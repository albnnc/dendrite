#include "app.hpp"

namespace dendrite
{

void App::updateDimensionDataFiles()
{
  for (auto it = field.clusterSteps.begin();
       it != field.clusterSteps.end();
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
    auto &dfData = (*df).data;
    if ((dfData.size() == 0 || count != dfData.back().x) &&
        (dimension >= 1 && dimension <= 2))
    {
      df->push(Vec2(count, dimension));
    }
  }
}

}; // namespace dendrite