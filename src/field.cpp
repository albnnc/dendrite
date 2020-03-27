#include "field.hpp"

namespace dendrite
{

Field::Field(Config &config) : fieldSize(config.get<int>("field", "initialFieldSize")),
                               sideResizeDelta(config.get<int>("field", "sideResizeDelta")),
                               populationMax(config.get<int>("field", "populationMax")),
                               populationCritical(config.get<int>("field", "populationCritical")),
                               particleActiveStepsMax(config.get<long long int>("field", "particleActiveStepsMax")),
                               particleBirthProbability(config.get<double>("field", "particleBirthProbability")),
                               particleRadius(config.get<double>("field", "particleRadius")),
                               particleDeltaMax(config.get<double>("field", "particleDeltaMax")),
                               particleDeltaShift(config.get<double>("field", "particleDeltaShift")),
                               interactionDelta(config.get<double>("field", "interactionDelta")),
                               interactionDeltaForFreeze(config.get<double>("field", "interactionDeltaForFreeze"))
{
  resize(fieldSize);
}

}; // namespace dendrite
