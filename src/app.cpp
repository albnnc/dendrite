#include "app.hpp"

namespace dendrite {

App::App(Config &config)
    : logLevel(config.get<int>("app", "logLevel")),
      windowSizePx(config.get<int>("app", "windowSizePx")),
      particleRadiusDeltaPx(
          config.get<double>("app", "particleRadiusDeltaPx")),
      sleepMs(config.get<int>("app", "sleepMs")),
      sleepMsIdle(config.get<int>("app", "sleepMsIdle")),
      stepsPerFrame(config.get<int>("app", "stepsPerFrame")),
      stepsPerDimensionDataFileEntry(
          config.get<int>("app", "stepsPerDimensionDataFileEntry")),
      hasLabels(config.get<bool>("app", "hasLabels")),
      hasGrid(config.get<bool>("app", "hasGrid")),
      mayIterate(config.get<bool>("app", "mayIterate")),
      mayUpdateDimensionDataFiles(
          config.get<bool>("app", "mayUpdateDimensionDataFiles")),
      backgroundColor(config.get<std::string>("app", "backgroundColor")),
      particleColor(config.get<std::string>("app", "particleColor")),
      isHeadless(config.get<bool>("app", "isHeadless")),
      hasToLoad(config.get<bool>("app", "hasToLoad")),
      dumpToLoad(config.get<std::string>("app", "dumpToLoad")),
      field(config) {
  if (!isHeadless) {
    window = new sf::RenderWindow(sf::VideoMode(windowSizePx, windowSizePx), "dendrite");
    font = new sf::Font();
    if (!font->loadFromFile("roboto.ttf")) {
      std::cout << "Unable to load font";
      exit(1);
    }
  }
}

}; // namespace dendrite
