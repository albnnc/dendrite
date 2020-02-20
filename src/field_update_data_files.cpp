#include "field.hpp"

namespace dendrite
{

void Field::updateDataFiles()
{
  for (auto it = rootSteps.begin(); it != rootSteps.end(); ++it)
  {
    int step = *it;
    auto df = std::find_if(
        dataFiles.begin(),
        dataFiles.end(),
        [step](const DataFile &d) {
          return d.title == std::to_string(step);
        });
    if (df == dataFiles.end())
    {
      dataFiles.push_back(DataFile(std::to_string(step)));
      df = dataFiles.end() - 1;
    }
    long long int count = countParticles(step);
    double dimension = countBoxes(step);
    auto &dfData = (*df).data;
    // if (dfData.size() == 0 || count != dfData.back().x)
    if ((dfData.size() == 0 || count != dfData.back().x) &&
        (dimension >= 1 && dimension <= 2))
    {
      df->push(Vec2(count, dimension));
    }
  }
}

}; // namespace dendrite
