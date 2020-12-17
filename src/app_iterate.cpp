#include "app.hpp"

namespace dendrite {

void App::iterate() {
  auto begin = std::chrono::system_clock::now();
  if (hasSingleStepPerFrame) {
    field.cycle();
  } else {
    for (int i = 0; i < stepsPerFrame; ++i) {
      field.cycle();
    }
  }
  if (logLevel >= 3) {
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - begin;
    double seconds = diff.count();
    std::cout << "Computed "
              << stepsPerFrame
              << " steps during "
              << seconds
              << " s ("
              << stepsPerFrame / seconds
              << " steps/s)"
              << std::endl;
  }
  if (mayUpdateDimensionDataFiles &&
      (dimensionDataFilesUpdateStep == -1 ||
       field.stepNumber - dimensionDataFilesUpdateStep >=
           stepsPerDimensionDataFileEntry)) {
    if (logLevel >= 3) {
      std::cout << "Update dimension data files" << std::endl;
    }
    dimensionDataFilesUpdateStep = field.stepNumber;
    updateDimensionDataFiles();
  }
}

}; // namespace dendrite
