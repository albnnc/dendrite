#include "app.hpp"

namespace dendrite {

void App::start() {
  while (window.isOpen()) {
    pollEvents();

    if (mayIterate) {
      iterate();
    }

    window.clear(getBackgroundColor());
    render();
    window.display();

    sf::sleep(sf::milliseconds(mayIterate ? sleepMs : sleepMsIdle));
  }
}

}; // namespace dendrite
