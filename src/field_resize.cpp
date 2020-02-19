#include "field.hpp"

namespace dendrite
{

void Field::resize(int size)
{
  int oldSize = data.size();
  for (int i = 0; i < oldSize; ++i)
  {
    data[i].resize(size, std::vector<Particle>(populationMax, Particle()));
    buff[i].resize(size, std::vector<Particle>(populationMax, Particle()));
  }
  data.resize(size,
              std::vector<std::vector<Particle>>(size, std::vector<Particle>(populationMax)));
  buff.resize(size,
              std::vector<std::vector<Particle>>(size, std::vector<Particle>(populationMax)));

  double xCenter = (double)size / 2;
  double yCenter = (double)size / 2;
  moveShifts.resize(size);
  for (int i = 0; i < size; ++i)
  {
    moveShifts[i].resize(size);
    for (int j = 0; j < size; ++j)
    {
      double dx = xCenter - (double)i;
      double dy = yCenter - (double)j;
      double d = std::sqrt(dx * dx + dy * dy);
      dx = d == 0 ? 0 : dx / d * particleDeltaShift;
      dy = d == 0 ? 0 : dy / d * particleDeltaShift;
      moveShifts[i][j] = {dx, dy};
    }
  }

  int gap = (size - oldSize) / 2;
  for (int i = size - 1; i >= 0; --i)
  {
    for (int j = size - 1; j >= 0; --j)
    {
      if (i < gap || j < gap)
      {
        data[i][j] = std::vector<Particle>(populationMax, Particle());
      }
      else if (i < size - gap && i < size - gap)
      {
        data[i][j] = data[i - gap][j - gap];
      }
    }
  }
}

}; // namespace dendrite
