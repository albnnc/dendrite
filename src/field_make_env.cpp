#include "field.hpp"

namespace dendrite {

void Field::makeEnv() {
  if (stepNumber != 1) {
    return;
  }

  if (fieldType == "migration") {
    int countPerCell = 1.0 / (particleRadius * 2.0);
    double deltaPerCell = 1.0 / (double)(countPerCell + 1);
    for (int i = 0; i < fieldSize; ++i) {
      int j = fieldSize - 1;
      Cell &cell = data[i][j];
      for (int k = 0; k < countPerCell; ++k) {
        cell[k].birthStep = 1;
        cell[k].freezeStep = 1;
        cell[k].clusterStep = 1;
        cell[k].x = -0.5 + deltaPerCell * (double)(k + 1);
        cell[k].y = 0.0;
      }
    }
  }
}

}; // namespace dendrite
