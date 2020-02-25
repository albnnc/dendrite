#include "app.hpp"

namespace dendrite
{

void App::pollEvents()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      window.close();
    }

    if (event.type == sf::Event::KeyReleased)
    {
      // std::cout << "Key pressed: " << event.key.code << std::endl;

      if (event.key.control && event.key.code == 18) // Ctrl + S
      {
        prepareOutDir();
        screenshot();
        std::cout << "Screenshot saved" << std::endl;
      }

      if (event.key.control && event.key.code == 3) // Ctrl + D
      {
        prepareOutDir();
        for (auto df : field.dimensionDataFiles)
        {
          df.write(outDir + "/" + df.title + ".dat");
        }
        std::cout << "Dimensions data files saved" << std::endl;
      }

      if (event.key.code == 57) // Space
      {
        std::cout << (mayIterate ? "Pause" : "Resume") << std::endl;
        mayIterate = !mayIterate;
      }

      if (event.key.code == 85) // F1
      {
        std::cout << (hasActiveParticles
                          ? "Hide active particles"
                          : "Show active particles")
                  << std::endl;
        hasActiveParticles = !hasActiveParticles;
      }

      if (event.key.code == 86) // F2
      {
        std::cout << (hasLabels
                          ? "Hide labels"
                          : "Show labels")
                  << std::endl;
        hasLabels = !hasLabels;
      }

      if (event.key.code == 87) // F3
      {
        std::cout << (hasGrid
                          ? "Hide grid"
                          : "Show grid")
                  << std::endl;
        hasGrid = !hasGrid;
      }
    }
  }
}

}; // namespace dendrite
