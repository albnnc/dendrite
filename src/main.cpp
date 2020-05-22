#include "app.hpp"
#include "config.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  dendrite::Config config;
  config.parse(argc, argv);

  omp_set_num_threads(
      std::min(
          config.get<int>("app", "desiredThreadsNumber"),
          omp_get_max_threads()));

  dendrite::App app(config);
  app.start();

  return 0;
}
