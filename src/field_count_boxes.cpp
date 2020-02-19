#include "field.hpp"

namespace dendrite
{

double Field::countBoxes(int rootStep)
{
  int interationsMax = 20;
  double boxSize = 1;
  double dimension = 2;
  for (int it = 0; it < interationsMax && boxSize >= particleRadius * 2; ++it)
  {
    int boxesPerSide = std::ceil((double)fieldSize / boxSize);
    int boxesPerCell = 1.0 / boxSize;
    int boxCount = 0;
    for (int i = 0; i < boxesPerSide; ++i)
    {
      for (int j = 0; j < boxesPerSide; ++j)
      {
        int xField = i / boxesPerCell;
        int yField = j / boxesPerCell;
        int xCell = i % boxesPerCell;
        int yCell = j % boxesPerCell;
        Vec2 min(boxSize * (double)xCell,
                 boxSize * (double)yCell);
        Vec2 max(boxSize * (double)(xCell + 1),
                 boxSize * (double)(yCell + 1));

        if (xField >= fieldSize || yField >= fieldSize)
        {
          continue;
        }

        auto &cell = data[xField][yField];
        for (int k = 0; k < populationMax; ++k)
        {
          if (cell[k].bornStep < 0)
          {
            break;
          }
          if (cell[k].freezeStep < 0)
          {
            continue;
          }
          Vec2 p = cell[k] - Vec2(-0.5, -0.5);
          if (p.x >= min.x && p.y >= min.y &&
              p.x <= max.x && p.y <= max.y)
          {
            ++boxCount;
            break;
          }
        }
      }
    }
    dimension = std::log((double)boxCount) / std::log((double)fieldSize / boxSize);
    boxSize *= 0.8;
  }

  // TODO: approx.

  return dimension;
}

}; // namespace dendrite
