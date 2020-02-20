#pragma once

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include "vec2.hpp"
#include "particle.hpp"
#include "data_file.hpp"

namespace dendrite
{

class Field
{
public:
  typedef std::vector<std::vector<std::vector<Particle>>> Data;
  long long int stepNumber = 1;
  int fieldSize;
  Data data = Data(0);
  std::vector<DataFile> dimensionDataFiles;

  int populationMax = 100;
  int populationCritical = 30;
  double particleBirthProbability = 0.01;
  double particleRadius = 0.05;
  double particleDeltaMax = 0.002;
  double particleDeltaShift = 0.003;
  double interactionDelta = 0.7;
  double interactionDeltaForFreeze = 0.2;

  Field(int size);

  void resize(int size);
  void born();
  void move();
  void sort();
  void arrange();
  void join();
  void collapse();
  void cycle();

  long long int countParticles(long long int clusterStep = -1);
  double countBoxes(long long int clusterStep = -1);
  void updateDimensionDataFiles();

private:
  bool hasAnyMoved = false;
  bool mayBorn = false;
  Vec2 fieldCenter;
  std::vector<long long int> clusterSteps;
};

}; // namespace dendrite
