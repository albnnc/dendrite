#include "field.hpp"

namespace dendrite
{

void Field::writeDataFiles()
{
  for (auto it = dataFiles.begin(); it != dataFiles.end(); ++it)
  {
    it->write();
  }
}

}; // namespace dendrite
