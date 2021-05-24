#include "app.hpp"

namespace dendrite {

void App::load() {

  std::ifstream in;
  in.open(dumpToLoad);
  int fieldSize = 0;
  int stepNumber = 0;
  in >> fieldSize;
  in >> stepNumber;

  field.resize(fieldSize);
  field.stepNumber = stepNumber;
  field.clusterSteps.clear();

  std::string line = "";
  int i = 0;
  int j = 0;
  while (true) {
    if (!std::getline(in, line)) {
      break;
    }
    std::istringstream ins(line);
    ins >> i >> j;
    auto it = std::find_if(
        field.data[i][j].begin(),
        field.data[i][j].end(),
        [](const Particle &p) {
          return p.birthStep < 0;
        });
    if (it == field.data[i][j].end()) {
      std::cout << "Unable to find space for dump" << std::endl;
      exit(1);
    }
    ins >> it->x >> it->y >> it->birthStep >> it->freezeStep >> it->clusterStep;
    if (it->clusterStep > 0 &&
        std::find(
            field.clusterSteps.begin(),
            field.clusterSteps.end(),
            it->clusterStep) != field.clusterSteps.end()) {
      field.clusterSteps.push_back(it->clusterStep);
    }
  }
}

}; // namespace dendrite
