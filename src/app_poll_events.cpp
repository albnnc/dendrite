#include "app.hpp"

namespace dendrite {

void App::pollEvents() {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window->close();
    }

    if (event.type == sf::Event::KeyReleased) {
      if (logLevel >= 2) {
        std::cout << "Key pressed: " << event.key.code << std::endl;
      }

      if (event.key.code == 57) // Space
      {
        std::cout << (mayIterate ? "Pause" : "Resume") << std::endl;
        mayIterate = !mayIterate;
      }

      if (event.key.code == 42) // Right Shift
      {
        std::cout << (hasSingleStepPerFrame
                          ? "Switch to multiple steps per frame"
                          : "Switch to single step per frame")
                  << std::endl;
        hasSingleStepPerFrame = !hasSingleStepPerFrame;
      }

      if (!mayIterate && event.key.code == 58) // Enter
      {
        iterate();
      }

      if (event.key.control && event.key.code == 18) // Ctrl + S
      {
        prepareOutDir();
        screenshot();
        std::cout << "Screenshot saved" << std::endl;
      }

      if (event.key.control && event.key.code == 3) // Ctrl + D
      {
        prepareOutDir();
        for (auto df : dimensionDataFiles) {
          df.write(outDir + "/" + df.title + ".dat");
        }
        std::cout << "Dimensions data files saved" << std::endl;
      }

      if (event.key.control && event.key.code == 5) // Ctrl + F
      {
        prepareOutDir();
        dump();
        std::cout << "Dump saved" << std::endl;
      }

      if (event.key.code == 0) // A
      {
        std::cout << (hasActiveParticles
                          ? "Hide active particles"
                          : "Show active particles")
                  << std::endl;
        hasActiveParticles = !hasActiveParticles;
      }

      if (event.key.code == 11) // L
      {
        std::cout << (hasLabels
                          ? "Hide labels"
                          : "Show labels")
                  << std::endl;
        hasLabels = !hasLabels;
      }

      if (event.key.code == 6) // G
      {
        std::cout << (hasGrid
                          ? "Hide grid"
                          : "Show grid")
                  << std::endl;
        hasGrid = !hasGrid;
      }

      if (event.key.code == 1) // B
      {
        std::cout << "Change background color"
                  << std::endl;
        backgroundColor = backgroundColor == "dark" ? "light" : "dark";
      }

      if (event.key.code == 15) // P
      {
        std::cout << "Change particles color"
                  << std::endl;
        if (particleColor == "gradient") {
          particleColor = "contrast";
        } else if (particleColor == "contrast") {
          particleColor = "cluster";
        } else if (particleColor == "cluster") {
          particleColor = "gradient";
        }
      }

      if (event.key.code == 17) // R
      {
        particleRadiusDeltaPx =
            particleRadiusDeltaPx + (event.key.shift ? -0.5 : 0.5);
        std::cout << "Change particles radius delta to "
                  << particleRadiusDeltaPx
                  << std::endl;
      }
    }
  }
}

}; // namespace dendrite
