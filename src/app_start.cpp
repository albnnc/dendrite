#include "app.hpp"

namespace dendrite
{

void App::start()
{
  std::srand(std::time(nullptr));
  omp_set_num_threads(
      std::min(desiredThreadsNumber, omp_get_max_threads()));

  while (window.isOpen())
  {
    pollEvents();

    if (mayIterate)
    {
      for (int i = 0; i < stepsPerFrame; ++i)
      {
        field.cycle();
      }
      if (mayUpdateDimensionDataFiles)
      {
        field.updateDimensionDataFiles();
      }
    }

    window.clear(backgroundColor == "dark" ? sf::Color::Black : sf::Color::White);
    render();
    window.display();

    sf::sleep(sf::milliseconds(mayIterate ? sleepMs : sleepMsIdle));
  }
}

}; // namespace dendrite
