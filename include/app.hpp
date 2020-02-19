#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "field.hpp"

namespace dendrite
{

class App
{
private:
  int windowSizePx = 800;
  int sleepMs = 5;
  int iterationsPerFrame = 100;
  sf::RenderWindow window;
  Field field;

public:
  App();

  void start();
  void render();
};

}; // namespace dendrite
