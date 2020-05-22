#include "random.hpp"

namespace dendrite {

Random::Random() {
  int threadsCount = 1;
#pragma omp parallel
  {
    threadsCount = omp_get_num_threads();
  }
  for (int i = 0; i < threadsCount; ++i) {
    std::random_device rd;
    std::mt19937 generator(rd());
    generators.push_back(generator);
  }
}

double Random::getDouble() {
  int threadNumber = omp_get_thread_num();
  double result = distribution(generators[threadNumber]);
  return result;
}

}; // namespace dendrite
