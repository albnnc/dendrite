#include "field.hpp"

namespace dendrite {

void Field::cycle() {
  bool canLog = logLevel >= 4;
  if (canLog) {
    std::cout << "Giving birth" << std::endl;
  }
  giveBirth();
  if (canLog) {
    std::cout << "Moving" << std::endl;
  }
  move();
  if (canLog) {
    std::cout << "Arranging" << std::endl;
  }
  arrange();
  if (canLog) {
    std::cout << "Sorting" << std::endl;
  }
  sort();
  if (canLog) {
    std::cout << "Joining" << std::endl;
  }
  join();
  if (canLog) {
    std::cout << "Arranging" << std::endl;
  }
  arrange();
  if (canLog) {
    std::cout << "Sorting" << std::endl;
  }
  sort();
  if (canLog) {
    std::cout << "Collapsing" << std::endl;
  }
  collapse();
  if (canLog) {
    std::cout << "Dieing" << std::endl;
  }
  die();
  if (canLog) {
    std::cout << "Resizing" << std::endl;
  }
  resize();
  ++stepNumber;
}

}; // namespace dendrite
