#include "field.hpp"

#pragma omp declare reduction(merge                         \
                              : std::vector <long long int> \
                              : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))

namespace dendrite {

void Field::collapse() {
#pragma omp parallel for reduction(merge \
                                   : clusterSteps)
  for (int i = 0; i < fieldSize; ++i) {
    for (int j = 0; j < fieldSize; ++j) {
      auto &cell = data[i][j];
      auto notFrozenFirst =
          std::find_if(
              cell.begin(),
              cell.end(),
              [](Particle &p) {
                return p.birthStep > 0 && p.freezeStep < 0;
              });

      if (notFrozenFirst == cell.end()) {
        continue;
      }

      auto notBornFirst = std::find_if(
          cell.begin(),
          cell.end(),
          [](Particle &p) { return p.birthStep < 0; });
      int count = std::distance(notFrozenFirst, notBornFirst);

      if (notBornFirst == cell.end()) {
        std::cout << "Cell overlow occured" << std::endl;
      }

      if (count >= populationCritical || notBornFirst == cell.end()) {
        Vec2 median = {0, 0};
        for (auto it = notFrozenFirst; it != notBornFirst; ++it) {
          median += (*it);
        }
        median /= count;
        std::fill(notFrozenFirst, notBornFirst, Particle());
        (*notFrozenFirst) =
            Particle(median.x, median.y, stepNumber, stepNumber, stepNumber);

        // TODO: на одном шаге может появиться несколько кластеров
        clusterSteps.push_back(stepNumber);
      }
    }
  }
}

}; // namespace dendrite
