#include "field.hpp"

namespace dendrite {

void Field::giveBirth() {
  mayGiveBirth = false;
  auto giveBirthInCell = [this](Cell &cell) {
    auto frozen = std::find_if(
        cell.begin(),
        cell.end(),
        [](const Particle &p) {
          return p.freezeStep > 0;
        });
    if (frozen != cell.end()) {
      return;
    }
    mayGiveBirth = true;
    int birthTries = 0;
    auto it = std::find_if(
        cell.begin(),
        cell.end(),
        [](const Particle &p) {
          return p.birthStep < 0;
        });

    while (it != cell.end() && birthTries < particleBirthTriesMax) {
      if (random.getDouble() < particleBirthProbability) {
        it->x = random.getDouble() - 0.5;
        it->y = random.getDouble() - 0.5;
        it->birthStep = stepNumber;
        ++it;
      }
      ++birthTries;
    }
  };

  if (fieldType == "bornuillon" && stepNumber != 1) {
    return;
  }

#pragma omp parallel for
  for (auto it = birthCells.begin();
       it != birthCells.end();
       ++it) {
    giveBirthInCell(*it);
  }
}

}; // namespace dendrite
