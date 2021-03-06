#include "field.hpp"

namespace dendrite {

void Field::resize(int forcedSize) {
  int size = data.size();
  if (size < 1) {
    // constructor call
    size = fieldSize;
  } else if (forcedSize > 0) {
    size = forcedSize;
  } else if (
      (fieldType != "shelling" || fieldSize >= fieldSizeMax) &&
      !mayGiveBirth && !hasAnyMoved) {
    isFinished = true;
    return;
  } else if (fieldType == "shelling" && !mayGiveBirth && !hasAnyMoved) {
    // shelling upscale
    size += sideResizeDelta;
  } else {
    return;
  }

  int oldSize = data.size();
  if (forcedSize > 0) {
    data.clear();
  } else {
    for (int i = 0; i < oldSize; ++i) {
      data[i].resize(
          size,
          std::vector<Particle>(populationMax, Particle()));
    }
  }
  data.resize(
      size,
      std::vector<std::vector<Particle>>(
          size,
          std::vector<Particle>(populationMax, Particle())));

  if (!forcedSize) {
    int gap = (size - oldSize) / 2;
    for (int i = size - 1; i >= 0; --i) {
      for (int j = size - 1; j >= 0; --j) {
        if (i < gap || j < gap) {
          data[i][j] = std::vector<Particle>(populationMax, Particle());
        } else if (i < size - gap && i < size - gap) {
          data[i][j] = data[i - gap][j - gap];
        }
      }
    }
  }

  fieldSize = data.size();
  fieldCenter = Vec2((double)fieldSize / 2, (double)fieldSize / 2);

  double peripheryRadius = (double)(fieldSize - 1) / 2;
  birthCells.clear();
  for (int i = 0; i < fieldSize; ++i) {
    for (int j = 0; j < fieldSize; ++j) {
      Cell &cell = data[i][j];
      if (fieldType == "bouillon" || fieldType == "immersion") {
        birthCells.push_back(cell);
      } else if (fieldType == "migration") {
        if (j == 0) {
          birthCells.push_back(cell);
        }
      } else if (fieldType == "shelling") {
        Vec2 cellCenter = Vec2(i, j);
        std::vector<Vec2> cellCorners = {
            cellCenter + Vec2(0, 0),
            cellCenter + Vec2(0, 1),
            cellCenter + Vec2(1, 0),
            cellCenter + Vec2(1, 1)};
        bool hasInside = false;
        bool hasOutside = false;
        for (auto it = cellCorners.begin(); it != cellCorners.end(); ++it) {
          if ((*it - fieldCenter).length() <= peripheryRadius) {
            hasInside = true;
          } else {
            hasOutside = true;
          }
        }
        if (hasInside && hasOutside) {
          birthCells.push_back(cell);
        }
      }
    }
  }

  if (logLevel >= 2) {
    std::cout << "Resized to " << size << "x" << size << std::endl;
  }
}

}; // namespace dendrite
