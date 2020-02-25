#include "app.hpp"

namespace dendrite
{

void App::render()
{
  int fieldSize = field.data.size();
  int cellSizePx = (windowSizePx / fieldSize);
  int particleRadiusPx = cellSizePx * field.particleRadius + 1;

  if (hasGrid)
  {
    for (int i = 0; i < fieldSize; ++i)
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
  }

  auto forEachParticle = [this,
                          fieldSize,
                          cellSizePx,
                          particleRadiusPx](
                             std::function<void(Particle p, Vec2 v)> fn) {
    for (int i = 0; i < fieldSize; ++i)
    {
      for (int j = 0; j < fieldSize; ++j)
      {
        for (int k = 0; k < field.populationMax; ++k)
        {
          Particle p = field.data[i][j][k];
          if (p.bornStep < 0)
          {
            break;
          }
          Vec2 v((i + 0.5 + p.x) * cellSizePx, (j + 0.5 + p.y) * cellSizePx);
          fn(p, v);
        }
      }
    }
  };

  forEachParticle([this, particleRadiusPx](Particle p, Vec2 v) {
    if (std::abs(p.x) > 0.5 || std::abs(p.y) > 0.5)
    {
      std::cout << "Particle out of bounds: " << p << std::endl;
    }
    if (p.freezeStep < 0 && !hasActiveParticles)
    {
      return;
    }
    sf::CircleShape circle(particleRadiusPx);
    circle.setOrigin(particleRadiusPx, particleRadiusPx);
    circle.setPosition(v.x, v.y);
    bool isFrozen = p.freezeStep > 0;

    sf::Color color(
        isFrozen ? (((double)p.freezeStep / (double)field.stepNumber) * 255) : 170,
        isFrozen ? 0 : 170,
        isFrozen ? 255 - (((double)p.freezeStep / (double)field.stepNumber) * 255) : 170);
    circle.setFillColor(color);
    window.draw(circle);
  });

  forEachParticle([this, cellSizePx, particleRadiusPx](Particle p, Vec2 v) {
    if (hasLabels && p.freezeStep > 0 && p.bornStep == p.clusterStep)
    {
      sf::Vertex line[] = {
          sf::Vertex(sf::Vector2f(v.x, v.y), sf::Color::White),
          sf::Vertex(sf::Vector2f(v.x + 20, v.y + 20), sf::Color::White)};
      window.draw(line, 2, sf::Lines);

      sf::Text text;
      text.setFont(font);
      text.setString("Cluster #" + std::to_string(p.clusterStep));
      text.setCharacterSize(14);
      text.setFillColor(sf::Color::White);
      text.setPosition(v.x + 25, v.y + 25);
      window.draw(text);
    }
  });
}

}; // namespace dendrite
