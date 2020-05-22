#include "field.hpp"

namespace dendrite {

void Field::cycle() {
  if (mayLogDebug) {
    std::cout << "born..." << std::endl;
  }
  born();
  if (mayLogDebug) {
    std::cout << "move..." << std::endl;
  }
  move();
  if (mayLogDebug) {
    std::cout << "join..." << std::endl;
  }
  join();
  if (mayLogDebug) {
    std::cout << "arrange..." << std::endl;
  }
  arrange();
  if (mayLogDebug) {
    std::cout << "sort..." << std::endl;
  }
  sort();
  if (mayLogDebug) {
    std::cout << "collapse..." << std::endl;
  }
  collapse();
  if (mayLogDebug) {
    std::cout << "die..." << std::endl;
  }
  die();
  if (mayLogDebug) {
    std::cout << "resize..." << std::endl;
  }
  resize();
  ++stepNumber;
}

}; // namespace dendrite
