#include "field.hpp"

namespace dendrite
{

void Field::updateDimensionDataFiles()
{
  for (auto it = clusterSteps.begin(); it != clusterSteps.end(); ++it)
  {
    int step = *it;
    auto df = std::find_if(
        dimensionDataFiles.begin(),
        dimensionDataFiles.end(),
        [step](const DataFile &d) {
          return d.title == std::to_string(step);
        });
    if (df == dimensionDataFiles.end())
    {
      dimensionDataFiles.push_back(DataFile(std::to_string(step)));
      df = dimensionDataFiles.end() - 1;
    }
    long long int count = countParticles(step);
    double dimension = countBoxes(step);
    auto &dfData = (*df).data;
    if ((dfData.size() == 0 || count != dfData.back().x) &&
        (dimension >= 1 && dimension <= 2))
    {
      df->push(Vec2(count, dimension));
    }
  }
}

}; // namespace dendrite
