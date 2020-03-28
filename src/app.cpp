#include "app.hpp"

namespace dendrite
{

App::App(Config &config) : desiredThreadsNumber(config.get<int>("app", "desiredThreadsNumber")),
                           windowSizePx(config.get<int>("app", "windowSizePx")),
                           particleRadiusDeltaPx(config.get<double>("app", "particleRadiusDeltaPx")),
                           sleepMs(config.get<int>("app", "sleepMs")),
                           sleepMsIdle(config.get<int>("app", "sleepMsIdle")),
                           stepsPerFrame(config.get<int>("app", "stepsPerFrame")),
                           hasLabels(config.get<bool>("app", "hasLabels")),
                           hasGrid(config.get<bool>("app", "hasGrid")),
                           mayIterate(config.get<bool>("app", "mayIterate")),
                           mayUpdateDimensionDataFiles(config.get<bool>("app", "mayUpdateDimensionDataFiles")),
                           mayLogKeys(config.get<bool>("app", "mayLogKeys")),
                           backgroundColor(config.get<std::string>("app", "backgroundColor")),
                           particleColor(config.get<std::string>("app", "particleColor")),
                           window(sf::VideoMode(windowSizePx, windowSizePx), "dendrite"),
                           field(config)
{
  if (!font.loadFromFile("roboto.ttf"))
  {
    std::cout << "Unable to load font";
    exit(1);
  }
}

}; // namespace dendrite
