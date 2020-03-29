#include "field.hpp"

namespace dendrite
{

void Field::cycle()
{
  born();
  move();
  join();
  arrange();
  sort();
  collapse();
  die();
  resize();
  ++stepNumber;
}

}; // namespace dendrite
