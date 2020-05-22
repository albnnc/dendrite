#pragma once

#include <iostream>
#include <omp.h>
#include <random>

namespace dendrite {

class Random {
public:
  Random();
  double getDouble();

private:
  std::uniform_real_distribution<> distribution =
      std::uniform_real_distribution<>(0.0, 1.0);
  std::vector<std::mt19937> generators;
};

}; // namespace dendrite
