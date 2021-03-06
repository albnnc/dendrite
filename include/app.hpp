#pragma once

#include "config.hpp"
#include "field.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <omp.h>

namespace dendrite {

class App {
public:
  App(Config &config);

  void start();
  void render();
  void iterate();
  void pollEvents();
  void screenshot();
  void dump();
  void load();

private:
  // config.ini group
  int logLevel;
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
  std::string backgroundColor;
  std::string particleColor;

  bool isHeadless;
  bool hasToLoad;
  std::string dumpToLoad;

  bool hasActiveParticles = true;
  bool hasSingleStepPerFrame = false;

  Field field;
  sf::RenderWindow *window;
  sf::Font *font;

  int dimensionDataFilesUpdateStep = -1;
  std::vector<DataFile> dimensionDataFiles;

  std::string outDir = "out";

  void prepareOutDir();
  void updateDimensionDataFiles();
  std::string getExecutableDir();
  std::string getCwd();
  sf::Color getContrastColor();
  sf::Color getBackgroundColor();
  sf::Color getClusterColor(int clusterIndex);
};

}; // namespace dendrite
