#include "app.hpp"

namespace dendrite {

void App::dump() {
  int fieldSize = field.data.size();
  std::string dumpData = "";
  dumpData +=
      std::to_string(fieldSize) + "\n" +
      std::to_string(field.stepNumber) + "\n";
  for (int i = 0; i < fieldSize; ++i) {
    for (int j = 0; j < fieldSize; ++j) {
      for (int k = 0; k < field.populationMax; ++k) {
        Particle p = field.data[i][j][k];
        if (p.birthStep < 0) {
          break;
        }
        dumpData +=
            std::to_string(i) + " " +
            std::to_string(j) + " " +
            std::to_string(p.x) + " " +
            std::to_string(p.y) + " " +
            std::to_string(p.birthStep) + " " +
            std::to_string(p.freezeStep) + " " +
            std::to_string(p.clusterStep) + "\n";
      }
    }
  }
  std::string path = "";
  path += outDir +
          "/field_" +
          std::to_string(field.stepNumber) +
          ".dump";
  std::ofstream out;
  if (logLevel >= 1) {
    std::cout << "Writing dump to \"" << path << "\"" << std::endl;
  }
  out.open(path);
  out << dumpData;
}

}; // namespace dendrite
