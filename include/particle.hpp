#pragma once

#include "vec2.hpp"

namespace dendrite {

class Particle : public Vec2 {
public:
  long long int birthStep = -1;
  long long int freezeStep = -1;
  long long int clusterStep = -1;

  Particle(
      double x = -1,
      double y = -1,
      long long int birthStep = -1,
      long long int freezeStep = -1,
      long long int clusterStep = -1) {
    this->x = x;
    this->y = y;
    this->birthStep = birthStep;
    this->freezeStep = freezeStep;
    this->clusterStep = clusterStep;
  }

  Particle &operator=(const Particle &p) {
    x = p.x;
    y = p.y;
    birthStep = p.birthStep;
    freezeStep = p.freezeStep;
    clusterStep = p.clusterStep;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const Particle &p) {
    os << "{"
       << p.x
       << ", "
       << p.y
       << ", "
       << p.birthStep
       << ", "
       << p.freezeStep
       << "}";
    return os;
  }
};

}; // namespace dendrite
