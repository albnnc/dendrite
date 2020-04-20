#include "app.hpp"

namespace dendrite
{

void App::updateDimensionDataFiles()
{
  auto stepsToUpdate(field.clusterSteps);
  if (
      std::find(
          stepsToUpdate.begin(),
          stepsToUpdate.end(),
          -1) == stepsToUpdate.end())
  {
    stepsToUpdate.push_back(-1);
  }

  for (auto it = stepsToUpdate.begin();
       it != stepsToUpdate.end();
       ++it)
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
    long long int count = field.countParticles(step);
    double dimension = field.countBoxes(step);
    if (dimension < 0)
    {
      continue;
    }
    auto &dfData = (*df).data;
    if ((dfData.size() == 0 || count != dfData.back().x) &&
        (dimension >= 1 && dimension <= 2))
    {
      df->push(Vec2(count, dimension));
    }
  }
}

}; // namespace dendrite
