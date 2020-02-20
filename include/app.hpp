#pragma once

#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "field.hpp"

namespace dendrite
{

class App
{
public:
  App();

  void start();
  void render();
  void pollEvents();
  void screenshot();

private:
  int windowSizePx = 1000;
  int sleepMs = 10;
  int sleepMsIdle = 300;
  int iterationsPerFrame = 100;

  bool mayIterate = true;
  bool hasActiveParticles = true;
  bool hasGrid = false;

  sf::RenderWindow window;
  Field field;

  std::string outDir = "out";

  void prepareOutDir();
};

}; // namespace dendrite
