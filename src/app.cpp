#include "app.hpp"

namespace dendrite
{

App::App() : window(sf::VideoMode(windowSizePx, windowSizePx), "dendrite"),
             field(3)
{
  if (!font.loadFromFile("roboto.ttf"))
  {
    std::cout << "Unable to load font";
    exit(1);
  }
}

}; // namespace dendrite
