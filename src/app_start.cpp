#include "app.hpp"

namespace dendrite {

void App::start() {
  while (window.isOpen()) {
    pollEvents();

    if (mayIterate) {
      for (int i = 0; i < stepsPerFrame; ++i) {
        field.cycle();
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
