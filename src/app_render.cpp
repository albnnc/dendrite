#include "app.hpp"

namespace dendrite {

// TODO: вынести в метод класса
void drawThickLine(
    sf::RenderTarget &target,
    const sf::Vector2f &p1,
    const sf::Vector2f &p2,
    sf::Color color = sf::Color::Black,
    float thickness = 1) {
  sf::Vertex vertices[4];
  sf::Vector2f direction = p2 - p1;
  sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
  sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

  sf::Vector2f offset = (thickness / 2.0f) * unitPerpendicular;

  vertices[0].position = p1 + offset;
  vertices[1].position = p2 + offset;
  vertices[2].position = p2 - offset;
  vertices[3].position = p1 - offset;

  for (int i = 0; i < 4; ++i) {
    vertices[i].color = color;
  }
  target.draw(vertices, 4, sf::Quads);
}

// TODO: вынести в метод класса
void drawPopup(
    sf::RenderTarget &target,
    const sf::Vector2f &position,
    const std::string data,
    sf::Font font,
    sf::Color color = sf::Color::Black,
    sf::Color outline = sf::Color::Black) {
  drawThickLine(target, position, position + sf::Vector2f(30, 30), outline, 4);
  drawThickLine(
      target,
      position + sf::Vector2f(1, 1),
      position + sf::Vector2f(29, 29),
      color,
      2);
  sf::Text text;
  text.setFont(font);
  text.setString(data);
  text.setCharacterSize(14);
  text.setFillColor(color);
  text.setOutlineColor(outline);
  text.setOutlineThickness(2);
  text.setPosition(position.x + 35, position.y + 35);
  target.draw(text);
}

void App::render() {
  int fieldSize = field.data.size();
  int cellSizePx = (windowSizePx / fieldSize);
  double particleRadiusPx =
      std::max(cellSizePx * field.particleRadius + particleRadiusDeltaPx, 0.5);
  sf::Vector2i mousePosition = sf::Mouse::getPosition() - window.getPosition();

  if (hasGrid) {
    for (int i = 0; i < fieldSize; ++i) {
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

  auto forEachParticle = [this, fieldSize, cellSizePx](
                             std::function<void(
                                 Particle particle,
                                 Vec2 position,
                                 Vec2 cellPosition)> fn) {
    for (int i = 0; i < fieldSize; ++i) {
      for (int j = 0; j < fieldSize; ++j) {
        for (int k = 0; k < field.populationMax; ++k) {
          Particle p = field.data[i][j][k];
          if (p.birthStep < 0) {
            break;
          }
          Vec2 cellPosition(i, j);
          Vec2 position = (cellPosition + Vec2(0.5, 0.5) + p) * cellSizePx;
          fn(p, position, cellPosition);
        }
      }
    }
  };

  forEachParticle([this, particleRadiusPx](
                      Particle particle,
                      Vec2 position,
                      Vec2 cellPosition) {
    if (std::abs(particle.x) > 0.5 || std::abs(particle.y) > 0.5) {
      std::cout << "Particle out of bounds: " << particle << std::endl;
    }
    if (particle.freezeStep < 0 && !hasActiveParticles) {
      return;
    }
    sf::CircleShape circle(particleRadiusPx);
    circle.setPosition(position.x, position.y);
    circle.setOrigin(particleRadiusPx, particleRadiusPx);
    bool isFrozen = particle.freezeStep > 0;
    sf::Color color;
    if (isFrozen) {
      if (particleColor == "gradient") {
        color = sf::Color(
            ((double)particle.freezeStep / (double)field.stepNumber) * 255,
            0,
            255 - (((double)particle.freezeStep / (double)field.stepNumber) * 255));
      } else if (particleColor == "contrast") {
        color = getContrastColor();
      } else if (particleColor == "cluster") {
        int clusterIndex =
            std::distance(field.clusterSteps.begin(),
                          std::find(field.clusterSteps.begin(),
                                    field.clusterSteps.end(),
                                    particle.clusterStep));
        color = getClusterColor(clusterIndex);
      }
    } else {
      color = sf::Color(130, 130, 130);
    }
    circle.setFillColor(color);
    window.draw(circle);
  });

  forEachParticle([this, cellSizePx, particleRadiusPx](
                      Particle particle,
                      Vec2 position,
                      Vec2 cellPosition) {
    if (hasLabels && particle.freezeStep > 0 && particle.birthStep == particle.clusterStep) {
      drawPopup(
          window,
          sf::Vector2f(position.x, position.y),
          "Cluster #" + std::to_string(particle.clusterStep),
          font,
          getContrastColor(),
          getBackgroundColor());
    }
  });

  forEachParticle([this, cellSizePx, particleRadiusPx, mousePosition](
                      Particle particle,
                      Vec2 position,
                      Vec2 cellPosition) {
    Vec2 mouseDelta = position - Vec2(mousePosition.x, mousePosition.y);
    if (hasLabels && mouseDelta.length() < particleRadiusPx) {
      drawPopup(
          window,
          sf::Vector2f(position.x, position.y),
          "Particle = {" +
              std::to_string(particle.birthStep) + ", " +
              std::to_string(particle.freezeStep) + ", " +
              std::to_string(particle.clusterStep) +
              "},\nPosition = {" +
              std::to_string(position.x) + ", " +
              std::to_string(position.y) +
              "},\nCell = {" +
              std::to_string(cellPosition.x) + ", " +
              std::to_string(cellPosition.y) +
              "}",
          font,
          getContrastColor(),
          getBackgroundColor());
    }
  });
}

} // namespace dendrite
