#include "app.hpp"

namespace dendrite {

void App::start() {
  while (window.isOpen()) {
    pollEvents();

    if (mayIterate) {
      for (int i = 0; i < stepsPerFrame; ++i) {
        auto begin = std::chrono::system_clock::now();
        field.cycle();
        if (mayLogDebug) {
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
      }
      if (mayUpdateDimensionDataFiles &&
          (dimensionDataFilesUpdateStep == -1 ||
           field.stepNumber - dimensionDataFilesUpdateStep >=
               stepsPerDimensionDataFileEntry)) {
        if (mayLogDebug) {
          std::cout << "Update dimension data files" << std::endl;
        }
        dimensionDataFilesUpdateStep = field.stepNumber;
        updateDimensionDataFiles();
      }
    }

    window.clear(backgroundColor == "dark" ? sf::Color::Black : sf::Color::White);
    render();
    window.display();

    sf::sleep(sf::milliseconds(mayIterate ? sleepMs : sleepMsIdle));
  }
}

}; // namespace dendrite
