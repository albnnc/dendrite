#include "field.hpp"

namespace dendrite {

void Field::move() {
  hasAnyMoved = false;
  hasSideParticles = false;

#pragma omp parallel for
  for (int i = 0; i < fieldSize; ++i) {
    for (int j = 0; j < fieldSize; ++j) {
      for (int k = 0; k < populationMax; ++k) {
        Particle &p = data[i][j][k];
        if (p.bornStep < 0) {
          break;
        }
        if (p.freezeStep > 0) {
          if (i == 0 || j == 0 || i == fieldSize - 1 || j == fieldSize - 1) {
            hasSideParticles = true;
          }
          continue;
        }
        Vec2 delta((random.getDouble() > 0.5 ? 1 : -1) * random.getDouble(),
                   (random.getDouble() > 0.5 ? 1 : -1) * random.getDouble());
        Vec2 shift = fieldCenter - Vec2(i + 0.5 + p.x, j + 0.5 + p.y);
        p += delta.normalize() * particleDeltaMax +
             shift.normalize() * particleDeltaShift;
        hasAnyMoved = true;
      }
    }
  }
}

}; // namespace dendrite
