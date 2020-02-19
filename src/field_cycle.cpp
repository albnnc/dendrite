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

  if (!mayBorn && !hasAnyMoved)
  {
    resize(data.size() + 4);
  }

  ++stepNumber;
}

}; // namespace dendrite
