#include "field.hpp"

namespace dendrite
{

void Field::join()
{
  int fieldSize = data.size();
  Vec2 fieldCenter = {(double)fieldSize / 2, (double)fieldSize / 2};

  // #pragma omp parallel for
  for (int i = 0; i < fieldSize; ++i)
  {
    for (int j = 0; j < fieldSize; ++j)
    {
      for (int k = 0; k < populationMax; ++k)
      {
        Particle &p = data[i][j][k];
        if (p.bornStep < 0)
        {
          // break;
          continue;
        }
        if (p.freezeStep > 0)
        {
          continue;
        }

        Vec2 translation(0, 0);
        double closestFrozenDistance = -1;
        long long int closestFrozenRootStep = -1;
        Vec2 closestFrozenNeighborPosition = {-1, -1};
        for (int x = i - 1; x <= i + 1; ++x)
        {
          for (int y = j - 1; y <= j + 1; ++y)
          {
            if (x < 0 || y < 0 || x >= fieldSize || y >= fieldSize)
            {
              continue;
            }
            for (int z = 0; z < populationMax; ++z)
            {
              if (x == i && y == j && z == k)
              {
                continue;
              }
              Particle &q = data[x][y][z];
              if (q.bornStep < 0)
              {
                // break;
                continue;
              }
              Vec2 d = Vec2(x - i, y - j) + q - p;
              double dLength = d.length();
              if (dLength <= interactionDeltaForFreeze && q.freezeStep > 0)
              {
                if (closestFrozenDistance == -1 || dLength < closestFrozenDistance)
                {
                  closestFrozenDistance = dLength;
                  closestFrozenRootStep = q.rootStep;
                  closestFrozenNeighborPosition =
                      p + d.normalize() * (dLength - particleRadius * 2);
                }
              }
              if (closestFrozenDistance == -1)
              {
                if (dLength < 2 * particleRadius)
                {
                  translation -= d.normalize() * particleRadius;
                }
                else if (dLength <= interactionDelta)
                {

                  translation += d / 2 / dLength / dLength;
                }
              }
            }
          }
          if (closestFrozenDistance == -1)
          {
            Vec2 shift = fieldCenter - Vec2(i + 0.5 + p.x, j + 0.5 + p.y);
            p += translation.normalize() * particleDeltaMax +
                 shift.normalize() * particleDeltaShift;
          }
          else
          {
            p.set(closestFrozenNeighborPosition.x,
                  closestFrozenNeighborPosition.y);
            p.freezeStep = stepNumber;
            p.rootStep = closestFrozenRootStep;
          }
        }
      }
    }
  }
}

}; // namespace dendrite
