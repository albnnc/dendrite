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
  double particleRadiusDeltaPx;
  int sleepMs;
  int sleepMsIdle;
  int stepsPerFrame;
  int stepsPerDimensionDataFileEntry;
  bool hasLabels;
  bool hasGrid;
  bool mayIterate;
  bool mayUpdateDimensionDataFiles;
  bool mayLogKeys;
  std::string backgroundColor;
  std::string particleColor;

  bool hasActiveParticles = true;

  sf::RenderWindow window;
  Field field;
  sf::Font font;

  int dimensionDataFilesUpdateStep = -1;
  std::vector<DataFile> dimensionDataFiles;

  std::string outDir = "out";

  void prepareOutDir();
  void updateDimensionDataFiles();
  std::string getExecutableDir();
  std::string getCwd();
  sf::Color getContrastColor();
};

}; // namespace dendrite
