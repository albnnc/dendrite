#include "field.hpp"

namespace dendrite
{

long long int Field::countParticles(long long int rootStep)
{
  long long int count = 0;

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
        if ((rootStep == -1 && p.freezeStep > 0) ||
            (rootStep == p.rootStep))
        {
          ++count;
        }
      }
    }
  }

  return count;
}

}; // namespace dendrite
