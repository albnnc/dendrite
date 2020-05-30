#include "field.hpp"

namespace dendrite {

void Field::cycle() {
  if (mayLogDebug) {
    std::cout << "Borning" << std::endl;
  }
  born();
  if (mayLogDebug) {
    std::cout << "Moving" << std::endl;
  }
  move();
  if (mayLogDebug) {
    std::cout << "Joining" << std::endl;
  }
  join();
  if (mayLogDebug) {
    std::cout << "Arranging" << std::endl;
  }
  arrange();
  if (mayLogDebug) {
    std::cout << "Sorting" << std::endl;
  }
  sort();
  if (mayLogDebug) {
    std::cout << "Collapsing" << std::endl;
  }
  collapse();
  if (mayLogDebug) {
    std::cout << "Dieing" << std::endl;
  }
  die();
  if (mayLogDebug) {
    std::cout << "Resizing" << std::endl;
  }
  resize();
  ++stepNumber;
}

}; // namespace dendrite
