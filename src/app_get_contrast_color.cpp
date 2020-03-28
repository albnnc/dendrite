#include "app.hpp"

namespace dendrite
{

sf::Color App::getContrastColor()
{
  return backgroundColor == "dark"
             ? sf::Color::White
             : sf::Color::Black;
}

}; // namespace dendrite
