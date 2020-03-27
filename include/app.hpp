#pragma once

#include <iostream>
#include <filesystem>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <omp.h>
#include "config.hpp"
#include "field.hpp"

namespace dendrite
{

class App
{
public:
  App(Config &config);

  void start();
  void render();
  void pollEvents();
  void screenshot();

private:
  // config.ini group
  int desiredThreadsNumber;
  int windowSizePx;
  int sleepMs;
  int sleepMsIdle;
  int iterationsPerFrame;
  bool hasLabels;
  bool hasGrid;
  sf::Color background;

  bool mayIterate = true;
  bool hasActiveParticles = true;

  sf::RenderWindow window;
  Field field;
  sf::Font font;

  std::string outDir = "out";

  void prepareOutDir();
};

}; // namespace dendrite
