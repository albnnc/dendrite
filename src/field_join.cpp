#include "field.hpp"

namespace dendrite
{

void Field::join()
{
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
          break;
        }
        if (p.freezeStep > 0)
        {
          continue;
        }

        Vec2 translation(0, 0);
        double closestFrozenDistance = -1;
        long long int closestFrozenClusterStep = -1;
        Vec2 closestFrozenNeighborPosition = {-1, -1};

        int gap = std::ceil(interactionDelta);
        for (int x = i - gap; x <= i + gap; ++x)
        {
          for (int y = j - gap; y <= j + gap; ++y)
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
                break;
              }
              Vec2 d = Vec2(x - i, y - j) + q - p;
              double dLength = d.length();
              if (dLength <= interactionDeltaForFreeze && q.freezeStep > 0)
              {
                if (closestFrozenDistance == -1 || dLength < closestFrozenDistance)
                {
                  closestFrozenDistance = dLength;
                  closestFrozenClusterStep = q.clusterStep;
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
                  Vec2 translationCandidate = d / 2 / dLength / dLength;
                  Vec2 translationMax = d - d.normalize() * 2 * particleRadius;
                  if (translationMax.length() < translationCandidate.length())
                  {
                    translation += translationMax;
                  }
                  else
                  {
                    translation += translationMax;
                  }
                }
              }
            }
          }
          if (closestFrozenDistance == -1)
          {
            p += translation.normalize() * particleDeltaMax;
          }
          else
          {
            p.set(closestFrozenNeighborPosition.x,
                  closestFrozenNeighborPosition.y);
            p.freezeStep = stepNumber;
            p.clusterStep = closestFrozenClusterStep;
          }
        }
      }
    }
  }
}

}; // namespace dendrite
