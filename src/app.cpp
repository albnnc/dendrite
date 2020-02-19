#include "app.hpp"

namespace dendrite
{

App::App() : window(sf::VideoMode(windowSizePx, windowSizePx), ":["),
             field(3)
{
}

void App::start()
{
  std::srand(0);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyReleased && event.key.code == 58)
      {
        field.countBoxes();
        std::cout << std::endl;
        std::cout << std::endl;
      }
      if (event.type == sf::Event::KeyReleased && event.key.code == 57)
      {
        mayIterate = !mayIterate;
      }
      // if (event.type == sf::Event::KeyReleased)
      // {
      //   std::cout << event.key.code << std::endl;
      // }
    }

    if (mayIterate)
    {
      for (int i = 0; i < iterationsPerFrame; ++i)
      {
        field.cycle();
      }
    }

    window.clear();
    render();
    window.display();
    sf::sleep(sf::milliseconds(sleepMs));
  }
}

void App::render()
{
  // sf::Color colors[3][3] = {
  //     {sf::Color(255, 0, 0), sf::Color(255, 128, 0), sf::Color(255, 255, 0)},
  //     {sf::Color(0, 255, 0), sf::Color(0, 255, 255), sf::Color(0, 0, 255)},
  //     {sf::Color(255, 0, 255), sf::Color(0, 128, 255), sf::Color(255, 255, 255)}};

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
        circle.setPosition(
            (i + 0.5 + p.x) * cellSizePx - particleRadiusPx * 0.5,
            (j + 0.5 + p.y) * cellSizePx - particleRadiusPx * 0.5);
        bool isFrozen = p.freezeStep > 0;
        sf::Color color(
            isFrozen ? (((double)p.freezeStep / (double)field.stepNumber) * 255) : 170,
            isFrozen ? 0 : 170,
            isFrozen ? 255 - (((double)p.freezeStep / (double)field.stepNumber) * 255) : 170);
        if (std::abs(p.x) > 0.5 || std::abs(p.y) > 0.5)
        {
          std::cout << "out of bounds: " << p << std::endl;
        }
        circle.setFillColor(color);
        window.draw(circle);
      }
    }
  }
}

}; // namespace dendrite
