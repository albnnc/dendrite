#include "app.hpp"

namespace dendrite
{

sf::Color App::getClusterColor(int clusterIndex)
{
  std::vector<sf::Color> colors = {
      sf::Color(200, 60, 0),
      sf::Color(80, 150, 190),
      sf::Color(55, 170, 120),
      sf::Color(215, 150, 100),
      sf::Color(200, 190, 80),
      sf::Color(200, 110, 150)};
  int size = colors.size();
  return colors[clusterIndex % size];
}

}; // namespace dendrite
