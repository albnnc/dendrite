#include "app.hpp"

namespace dendrite {

void App::start() {
  if (hasToLoad) {
    if (logLevel >= 1) {
      std::cout << "Loading dump" << std::endl;
    }
    load();
  }
  if (isHeadless) {
    if (logLevel >= 1) {
      std::cout << "Starting headless" << std::endl;
    }
    while (true) {
      if (field.isFinished) {
        if (logLevel >= 1) {
          std::cout << "Finished iterating, dumping and exiting now" << std::endl;
        }
        prepareOutDir();
        dump();
        exit(0);
      }
      iterate();
    }
  } else {
    if (logLevel >= 1) {
      std::cout << "Starting windowed" << std::endl;
    }
    while (window->isOpen()) {
      if (field.isFinished && mayIterate) {
        mayIterate = false;
        if (logLevel >= 1) {
          std::cout << "Finished iterating, paused" << std::endl;
        }
      }
      pollEvents();
      if (mayIterate) {
        iterate();
      }
      window->clear(getBackgroundColor());
      render();
      window->display();
      sf::sleep(sf::milliseconds(mayIterate ? sleepMs : sleepMsIdle));
    }
  }
}

}; // namespace dendrite
