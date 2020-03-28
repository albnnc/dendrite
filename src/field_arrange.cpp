#include "field.hpp"

namespace dendrite
{

void Field::arrange()
{
  std::vector<std::vector<int>> populations(
      fieldSize, std::vector<int>(fieldSize));
#pragma omp parallel for
  for (int i = 0; i < fieldSize; ++i)
  {
    for (int j = 0; j < fieldSize; ++j)
    {
      auto it = std::find_if(
          data[i][j].begin(),
          data[i][j].end(),
          [](const Particle &p) {
            return p.bornStep < 0;
          });
      populations[i][j] = std::distance(data[i][j].begin(), it);
    }
  }

  for (int i = 0; i < fieldSize; ++i)
  {
    for (int j = 0; j < fieldSize; ++j)
    {
      for (int k = 0; k < populationMax; ++k)
      {
        Particle p = data[i][j][k];
        if (p.bornStep < 0)
        {
          break;
        }
        Vec2 delta(std::round(p.x), std::round(p.y));
        int x = i + delta.x;
        int y = j + delta.y;
        if (x < 0 || y < 0 || x >= fieldSize || y >= fieldSize)
        {
          data[i][j][k] = Particle();
          --populations[i][j];
        }
        else if (x != i || y != j)
        {
          p -= delta;
          data[i][j][k] = Particle();
          --populations[i][j];
          if (populations[x][y] < populationMax - 2)
          {
            data[x][y][populations[x][y]] = p;
            ++populations[x][y];
          }
          else
          {
            std::cout << "Unable to move particle to cell "
                      << Vec2(x, y)
                      << ", removing it";
          }
        }
      }
    }
  }
}

}; // namespace dendrite
