#include "app.hpp"

namespace dendrite
{

void App::render()
{
  int fieldSize = field.data.size();
  int cellSizePx = (windowSizePx / fieldSize);
  double particleRadiusPx = std::max(
      cellSizePx * field.particleRadius + particleRadiusDeltaPx,
      0.5);

  if (hasGrid)
  {
    for (int i = 0; i < fieldSize; ++i)
    {
      sf::Color color(130, 130, 130, 130);
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
                          cellSizePx](
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

    sf::Color color;
    if (isFrozen)
    {
      if (particleColor == "gradient")
      {
        color = sf::Color(
            ((double)p.freezeStep / (double)field.stepNumber) * 255,
            0,
            255 - (((double)p.freezeStep / (double)field.stepNumber) * 255));
      }
      else if (particleColor == "contrast")
      {
        color = getContrastColor();
      }
      else if (particleColor == "cluster")
      {
        int clusterIndex =
            std::distance(
                field.clusterSteps.begin(),
                std::find(
                    field.clusterSteps.begin(),
                    field.clusterSteps.end(),
                    p.clusterStep));
        color = getClusterColor(clusterIndex);
      }
    }
    else
    {
      color = sf::Color(130, 130, 130);
    }
    circle.setFillColor(color);
    window.draw(circle);
  });

  forEachParticle([this, cellSizePx, particleRadiusPx](Particle p, Vec2 v) {
    if (hasLabels && p.freezeStep > 0 && p.bornStep == p.clusterStep)
    {
      sf::Color color = getContrastColor();
      sf::Vertex line[] = {
          sf::Vertex(sf::Vector2f(v.x, v.y), color),
          sf::Vertex(sf::Vector2f(v.x + 20, v.y + 20), color)};
      window.draw(line, 2, sf::Lines);

      sf::Text text;
      text.setFont(font);
      text.setString("Cluster #" + std::to_string(p.clusterStep));
      text.setCharacterSize(14);
      text.setFillColor(color);
      text.setPosition(v.x + 25, v.y + 25);
      window.draw(text);
    }
  });
}

}; // namespace dendrite
