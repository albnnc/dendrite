#include "field.hpp"

namespace dendrite
{

void Field::arrange()
{
  int fieldSize = data.size();
  std::vector<std::vector<int>> populations(
      fieldSize, std::vector<int>(fieldSize));

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
        double sx = std::round(p.x);
        double sy = std::round(p.y);
        int x = i + sx;
        int y = j + sy;
        if (x < 0 || y < 0 || x >= fieldSize || y >= fieldSize)
        {
          data[i][j][k] = Particle();
          --populations[i][j];
        }
        else if (x != i || y != j)
        {
          p.x = p.x - sx;
          p.y = p.y - sy;
          data[i][j][k] = Particle();
          data[x][y][populations[x][y]] = p;
          --populations[i][j];
          ++populations[x][y];
        }
      }
    }
  }
}

}; // namespace dendrite
