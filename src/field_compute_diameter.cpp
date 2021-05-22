#include "field.hpp"

namespace dendrite {

double Field::computeDiameter(long long int clusterStep) {
  Vec2 minField(-1, -1);
  Vec2 maxField(-1, -1);
  int dSqField = -1;

  auto hasTargetParticles = [this, clusterStep](int i, int j) {
    return std::find_if(
               data[i][j].begin(),
               data[i][j].end(),
               [clusterStep](const Particle &p) {
                 return clusterStep > 0
                            ? clusterStep == p.clusterStep
                            : p.freezeStep > 0;
               }) != data[i][j].end();
  };

  for (int i = 0; i < fieldSize; ++i) {
    for (int j = 0; j < fieldSize; ++j) {
      if (!hasTargetParticles(i, j)) {
        continue;
      }
      for (int x = 0; x < fieldSize; ++x) {
        for (int y = 0; y < fieldSize; ++y) {
          if (!hasTargetParticles(x, y)) {
            continue;
          }
          int t = (x - i) * (x - i) + (y - j) * (y - j);
          if (t > dSqField) {
            minField.set(i, j);
            maxField.set(x, y);
            dSqField = t;
          }
        }
      }
    }
  }

  if (minField == Vec2(-1, -1) || maxField == Vec2(-1, -1)) {
    return -1;
  }

  double diameter = -1;
  Vec2 translation = maxField - minField;

  for (int k = 0; k < populationMax; ++k) {
    auto p = data[minField.x][minField.y][k];
    if (p.birthStep < 0) {
      break;
    }
    if (clusterStep > 0 && clusterStep != p.clusterStep) {
      continue;
    }

    for (int z = 0; z < populationMax; ++z) {
      auto q = data[maxField.x][maxField.y][z];
      if (q.birthStep < 0) {
        break;
      }
      if (clusterStep > 0 && clusterStep != q.clusterStep) {
        continue;
      }

      double t = (translation + q - p).length();
      if (t > diameter) {
        diameter = t;
      }
    }
  }

  return diameter;
}

}; // namespace dendrite
