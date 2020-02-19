#include "field.hpp"

namespace dendrite
{

void Field::move()
{
  int fieldSize = data.size();
  hasAnyMoved = false;

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
        double dx = ((double)rand() / RAND_MAX > 0.5 ? 1 : -1) *
                    (double)rand() / RAND_MAX * particleDeltaMax;
        double dy = ((double)rand() / RAND_MAX > 0.5 ? 1 : -1) *
                    (double)rand() / RAND_MAX * particleDeltaMax;
        p.x += dx + moveShifts[i][j].x;
        p.y += dy + moveShifts[i][j].y;
        // p.x -= 0.01;
        // p.y += 0.01;
        hasAnyMoved = true;
      }
    }
  }
}

}; // namespace dendrite
