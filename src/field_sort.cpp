#include "field.hpp"

namespace dendrite {

void Field::sort() {
#pragma omp parallel for
  for (int i = 0; i < fieldSize; ++i) {
    for (int j = 0; j < fieldSize; ++j) {
      std::sort(
          data[i][j].begin(),
          data[i][j].end(),
          [](const Particle &a, const Particle &b) {
            if (a.freezeStep > 0 && b.freezeStep < 0) {
              return true;
            }
            if (a.bornStep > 0 && b.bornStep < 0) {
              return true;
            }
            return false;
          });
    }
  }
}

}; // namespace dendrite
