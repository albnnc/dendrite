#pragma once

#include <iostream>
#include <filesystem>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <omp.h>
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
  int desiredThreadsNumber = 8;
  int windowSizePx = 1000;
  int sleepMs = 10;
  int sleepMsIdle = 300;
  int iterationsPerFrame = 100;

  bool mayIterate = true;
  bool hasActiveParticles = true;
  bool hasLabels = false;
  bool hasGrid = false;

  sf::RenderWindow window;
  Field field;
  sf::Font font;

  std::string outDir = "out";

  void prepareOutDir();
};

}; // namespace dendrite
