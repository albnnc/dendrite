#include "field.hpp"

namespace dendrite {

Field::Field(Config &config)
    : logLevel(config.get<int>("field", "logLevel")),
      fieldSize(config.get<int>("field", "fieldSize")),
      fieldType(config.get<std::string>("field", "fieldType")),
      sideResizeDelta(config.get<int>("field", "sideResizeDelta")),
      populationMax(config.get<int>("field", "populationMax")),
      populationCritical(config.get<int>("field", "populationCritical")),
      particleActiveStepsMax(config.get<long long int>("field", "particleActiveStepsMax")),
      particleBirthProbability(config.get<double>("field", "particleBirthProbability")),
      particleBirthTriesMax(config.get<int>("field", "particleBirthTriesMax")),
      particleRadius(config.get<double>("field", "particleRadius")),
      particleMoveDelta(config.get<double>("field", "particleMoveDelta")),
      particleMoveDeltaShift(config.get<double>("field", "particleMoveDeltaShift")),
      particleJoinDeltaCoeff(config.get<double>("field", "particleJoinDeltaCoeff")),
      interactionDelta(config.get<double>("field", "interactionDelta")),
      interactionDeltaForFreeze(config.get<double>("field", "interactionDeltaForFreeze")) {
  resize();
  cycle();
}

}; // namespace dendrite
