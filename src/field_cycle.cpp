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
  if (particleBirthStrategy == "periphery" && !mayBorn && !hasAnyMoved)
  {
    resize(data.size() + sideResizeDelta);
  }
  ++stepNumber;
}

}; // namespace dendrite
