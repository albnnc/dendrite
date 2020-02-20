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
  if (!mayBorn && !hasAnyMoved)
  {
    resize(std::max(data.size() + sideResizeDelta * 2, (size_t)((double)data.size() * 1.3)));
  }
  ++stepNumber;
}

}; // namespace dendrite
