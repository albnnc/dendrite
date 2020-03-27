#include "app.hpp"

namespace dendrite
{

App::App(Config &config) : desiredThreadsNumber(config.get<int>("app", "desiredThreadsNumber")),
                           windowSizePx(config.get<int>("app", "windowSizePx")),
                           sleepMs(config.get<int>("app", "sleepMs")),
                           sleepMsIdle(config.get<int>("app", "sleepMsIdle")),
                           stepsPerFrame(config.get<int>("app", "stepsPerFrame")),
                           hasLabels(config.get<bool>("app", "hasLabels")),
                           hasGrid(config.get<bool>("app", "hasGrid")),
                           background(
                               config.get<std::string>("app", "background") == "dark"
                                   ? sf::Color::Black
                                   : sf::Color::White),
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
