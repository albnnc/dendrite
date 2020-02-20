#include "app.hpp"

namespace dendrite
{

void App::render()
{
  int fieldSize = field.data.size();
  int cellSizePx = (windowSizePx / fieldSize);
  int particleRadiusPx = cellSizePx * field.particleRadius + 1;
  sf::CircleShape circle(particleRadiusPx);

  for (int i = 0; i < fieldSize; ++i)
  {
    if (hasGrid)
    {
      sf::Color color(50, 50, 50);
      sf::Vertex line1[] = {
          sf::Vertex(sf::Vector2f((i + 1) * cellSizePx, 0), color),
          sf::Vertex(sf::Vector2f((i + 1) * cellSizePx, windowSizePx), color)};
      sf::Vertex line2[] = {
          sf::Vertex(sf::Vector2f(0, (i + 1) * cellSizePx), color),
          sf::Vertex(sf::Vector2f(windowSizePx, (i + 1) * cellSizePx), color)};
      window.draw(line1, 2, sf::Lines);
      window.draw(line2, 2, sf::Lines);
    }

    for (int j = 0; j < fieldSize; ++j)
    {
      for (int k = 0; k < field.populationMax; ++k)
      {
        Particle p = field.data[i][j][k];
        if (p.bornStep < 0)
        {
          break;
        }
        if (std::abs(p.x) > 0.5 || std::abs(p.y) > 0.5)
        {
          std::cout << "Particle out of bounds: " << p << std::endl;
        }
        if (p.freezeStep < 0 && !hasActiveParticles)
        {
          continue;
        }

        circle.setPosition(
            (i + 0.5 + p.x) * cellSizePx - particleRadiusPx * 0.5,
            (j + 0.5 + p.y) * cellSizePx - particleRadiusPx * 0.5);

        bool isFrozen = p.freezeStep > 0;
        sf::Color color(
            isFrozen ? (((double)p.freezeStep / (double)field.stepNumber) * 255) : 170,
            isFrozen ? 0 : 170,
            isFrozen ? 255 - (((double)p.freezeStep / (double)field.stepNumber) * 255) : 170);

        circle.setFillColor(color);
        window.draw(circle);
      }
    }
  }
}

}; // namespace dendrite
