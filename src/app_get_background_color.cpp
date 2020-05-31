#include "app.hpp"

namespace dendrite {

sf::Color App::getBackgroundColor() {
  return backgroundColor == "dark"
             ? sf::Color::Black
             : sf::Color::White;
}

}; // namespace dendrite
