#include "field.hpp"

namespace dendrite
{

void Field::born()
{
  mayBorn = false;
  auto bornInCell = [this](Cell &cell) {
    auto frozen = std::find_if(
        cell.begin(),
        cell.end(),
        [](const Particle &p) {
          return p.freezeStep > 0;
        });
    if (frozen != cell.end())
    {
      return;
    }
    mayBorn = true;
    int birthTries = 0;
    auto it = std::find_if(
        cell.begin(),
        cell.end(),
        [](const Particle &p) {
          return p.bornStep < 0;
        });
    while (it != cell.end() && birthTries < particleBirthTriesMax)
    {
      if ((double)std::rand() / RAND_MAX < particleBirthProbability)
      {
        it->x = (double)std::rand() / RAND_MAX - 0.5;
        it->y = (double)std::rand() / RAND_MAX - 0.5;
        it->bornStep = stepNumber;
        ++it;
      }
      ++birthTries;
    }
  };

  if (particleBirthStrategy == "bouillon" && stepNumber == 1)
  {
#pragma omp parallel for
    for (int i = 0; i < fieldSize; ++i)
    {
      for (int j = 0; j < fieldSize; ++j)
      {
        bornInCell(data[i][j]);
      }
    }
  }

  if (particleBirthStrategy == "periphery")
  {
#pragma omp parallel for
    for (auto it = peripheryCells.begin();
         it != peripheryCells.end();
         ++it)
    {
      bornInCell(*it);
    }
  }
}

}; // namespace dendrite
