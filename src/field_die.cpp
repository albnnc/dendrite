#include "field.hpp"

namespace dendrite {

void Field::die() {
  bool hasDied = false;

#pragma omp parallel for
  for (int i = 0; i < fieldSize; ++i) {
    for (int j = 0; j < fieldSize; ++j) {
      for (int k = 0; k < populationMax; ++k) {
        Particle &p = data[i][j][k];
        if (p.bornStep < 0) {
          break;
        }
        if (p.freezeStep > 0) {
          continue;
        }
        if (stepNumber - p.bornStep > particleActiveStepsMax) {
          p = Particle();
          hasDied = true;
        }
      }
    }
  }

  if (hasDied) {
    sort();
  }
}

}; // namespace dendrite
