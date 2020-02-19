#include "field.hpp"

namespace dendrite
{

void Field::born()
{
  mayBorn = false;
  int fieldSize = data.size();
  // #pragma omp parallel for
  for (int i = 0; i < fieldSize; ++i)
  {
    for (int j = 0; j < fieldSize; ++j)
    {
      if (i > 0 &&
          j > 0 &&
          i < fieldSize - 1 &&
          j < fieldSize - 1)
      {
        continue;
      }
      for (int k = 0; k < populationMax; ++k)
      {
        Particle &p = data[i][j][k];
        if (k > 0 && data[i][j][k - 1].bornStep < 0)
        {
          break;
        }
        if (p.bornStep > 0)
        {
          if (p.freezeStep > 0)
          {
            break;
          }
          continue;
        }
        mayBorn = true;
        if ((double)std::rand() / RAND_MAX < particleBirthProbability)
        {
          p.x = (double)rand() / RAND_MAX - 0.5;
          p.y = (double)rand() / RAND_MAX - 0.5;
          p.bornStep = stepNumber;
        }
      }
    }
  }
}

}; // namespace dendrite
