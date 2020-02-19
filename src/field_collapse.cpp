#include "field.hpp"

namespace dendrite
{

void Field::collapse()
{
  int fieldSize = data.size();
  // #pragma omp parallel for
  for (int i = 0; i < fieldSize; ++i)
  {
    for (int j = 0; j < fieldSize; ++j)
    {
      auto &cell = data[i][j];
      auto notFrozenFirst = std::find_if(
          cell.begin(),
          cell.end(),
          [](Particle &p) {
            return p.bornStep > 0 && p.freezeStep < 0;
          });

      if (notFrozenFirst == cell.end())
      {
        continue;
      }

      auto notBornFirst = std::find_if(
          cell.begin(),
          cell.end(),
          [](Particle &p) {
            return p.bornStep < 0;
          });

      int count = std::distance(notFrozenFirst, notBornFirst);
      if (count >= populationCritical)
      {
        Vec2 median = {0, 0};
        for (auto it = notFrozenFirst; it != notBornFirst; ++it)
        {
          median += (*it);
        }
        median /= count;
        std::fill(notFrozenFirst, notBornFirst, Particle());
        (*notFrozenFirst) = Particle(
            median.x,
            median.y,
            stepNumber,
            stepNumber,
            stepNumber);
      }
    }
  }
}

}; // namespace dendrite
