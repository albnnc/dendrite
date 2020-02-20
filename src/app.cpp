#include "app.hpp"

namespace dendrite
{

App::App() : window(sf::VideoMode(windowSizePx, windowSizePx), "dendrite"),
             field(3)
{
}

}; // namespace dendrite
