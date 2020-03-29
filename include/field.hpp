#pragma once

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include "config.hpp"
#include "vec2.hpp"
#include "particle.hpp"
#include "data_file.hpp"

namespace dendrite
{

class Field
{
public:
  typedef std::vector<Particle> Cell;
  typedef std::vector<std::vector<Cell>> Data;
  Data data = Data(0);
  std::vector<DataFile> dimensionDataFiles;

  long long int stepNumber = 1;

  // config.ini group
  int fieldSize;
  std::string fieldType;
  int sideResizeDelta;
  int populationMax;
  int populationCritical;
  long long int particleActiveStepsMax;
  double particleBirthProbability;
  int particleBirthTriesMax;
  double particleRadius;
  double particleDeltaMax;
  double particleDeltaShift;
  double interactionDelta;
  double interactionDeltaForFreeze;

  Field(Config &config);

  void resize(int size);
  void born();
  void die();
  void move();
  void sort();
  void arrange();
  void join();
  void collapse();
  void cycle();

  long long int countParticles(long long int clusterStep = -1);
  double countBoxes(long long int clusterStep = -1);
  double computeDiameter(long long int clusterStep = -1);
  void updateDimensionDataFiles();

private:
  bool hasAnyMoved = false;
  bool hasSideParticles = false;
  bool mayBorn = false;
  Vec2 fieldCenter;
  std::vector<long long int> clusterSteps;
  std::vector<std::reference_wrapper<Cell>> shellingCells;
};

}; // namespace dendrite
