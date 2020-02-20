#include "app.hpp"

namespace dendrite
{

void App::start()
{
  std::srand(0);

  while (window.isOpen())
  {
    pollEvents();

    if (mayIterate)
    {
      for (int i = 0; i < iterationsPerFrame; ++i)
      {
        field.cycle();
      }
      field.updateDimensionDataFiles();
    }

    window.clear();
    render();
    window.display();

    sf::sleep(sf::milliseconds(mayIterate ? sleepMs : sleepMsIdle));
  }
}

}; // namespace dendrite
