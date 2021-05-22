#pragma once

#include "config.hpp"
#include "data_file.hpp"
#include "particle.hpp"
#include "random.hpp"
#include "vec2.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace dendrite {

class Field {
public:
  typedef std::vector<Particle> Cell;
  typedef std::vector<std::vector<Cell>> Data;
  Data data = Data(0);
  std::vector<long long int> clusterSteps;

  long long int stepNumber = 1;

  // config.ini group
  int logLevel;
  int fieldSize;
  std::string fieldType;
  int sideResizeDelta;
  int populationMax;
  int populationCritical;
  long long int particleActiveStepsMax;
  double particleBirthProbability;
  int particleBirthTriesMax;
  double particleRadius;
  double particleMoveDelta;
  double particleMoveDeltaShift;
  double particleJoinDeltaCoeff;
  double interactionDelta;
  double interactionDeltaForFreeze;

  Field(Config &config);

  void resize();
  void born();
  void die();
  void move();
  void sort();
  void arrange();
  void join();
  void collapse();
  void cycle();

  long long int countParticles(long long int clusterStep = -1);
  double computeDiameter(long long int clusterStep = -1);
  double countBoxes(long long int clusterStep = -1);

private:
  bool hasAnyMoved = false;
  bool hasSideParticles = false;
  bool mayBorn = false;
  Vec2 fieldCenter;
  std::vector<std::reference_wrapper<Cell>> birthCells;
  Random random;
};

}; // namespace dendrite
