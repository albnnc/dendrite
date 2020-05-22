#include "app.hpp"

namespace dendrite {

void App::prepareOutDir() {
  if (std::filesystem::is_directory(outDir)) {
    return;
  }
  std::filesystem::create_directory(outDir);
}

}; // namespace dendrite
