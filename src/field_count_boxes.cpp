#include "field.hpp"

namespace dendrite {

double normalEq2(std::vector<double> x, std::vector<double> y) {
  int size = x.size();
  double xtx[2][2] = {{0, 0}, {0, 0}};
  for (int i = 0; i < size; i++) {
    xtx[0][1] += x[i];
    xtx[0][0] += x[i] * x[i];
  }
  xtx[1][0] = xtx[0][1];
  xtx[1][1] = size;

  // inverse
  double xtxInv[2][2] = {{0, 0}, {0, 0}};
  double d = 1 / (xtx[0][0] * xtx[1][1] - xtx[1][0] * xtx[0][1]);
  xtxInv[0][0] = xtx[1][1] * d;
  xtxInv[0][1] = -xtx[0][1] * d;
  xtxInv[1][0] = -xtx[1][0] * d;
  xtxInv[1][1] = xtx[0][0] * d;

  // times x^t
  std::vector<std::vector<double>> xtxInvxt(
      2, std::vector<double>(size, 0));

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < size; j++) {
      xtxInvxt[i][j] = xtxInv[i][0] * x[j] + xtxInv[i][1];
    }
  }

  // times y
  double theta[2] = {0, 0};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < size; j++) {
      theta[i] += xtxInvxt[i][j] * y[j];
    }
  }

  return theta[0];
}

double Field::countBoxes(long long int clusterStep) {
  int interationsMax = 20;
  double boxSize = 1.0;
  std::vector<double> x;
  std::vector<double> y;

  for (int it = 0; it < interationsMax && boxSize >= particleRadius; ++it) {
    int boxesPerSide = std::ceil((double)fieldSize / boxSize);
    int boxesPerCell = 1.0 / boxSize;
    int boxCount = 0;

    for (int i = 0; i < boxesPerSide; ++i) {
      for (int j = 0; j < boxesPerSide; ++j) {
        int xField = i / boxesPerCell;
        int yField = j / boxesPerCell;
        int xCell = i % boxesPerCell;
        int yCell = j % boxesPerCell;
        Vec2 minCell(boxSize * (double)xCell,
                     boxSize * (double)yCell);
        Vec2 maxCell(boxSize * (double)(xCell + 1),
                     boxSize * (double)(yCell + 1));

        if (xField >= fieldSize || yField >= fieldSize) {
          continue;
        }

        auto &cell = data[xField][yField];
        for (int k = 0; k < populationMax; ++k) {
          if (cell[k].birthStep < 0) {
            break;
          }
          if ((cell[k].freezeStep < 0) ||
              (clusterStep != -1 && clusterStep != cell[k].clusterStep)) {
            continue;
          }
          Vec2 p = cell[k] - Vec2(-0.5, -0.5);
          if (p.x >= minCell.x && p.y >= minCell.y &&
              p.x <= maxCell.x && p.y <= maxCell.y) {
            ++boxCount;
            break;
          }
        }
      }
    }
    x.push_back(boxSize);
    y.push_back(boxCount);
    boxSize *= 0.9;
  }

  double clusterSize = computeDiameter(clusterStep);
  if (clusterSize == -1) {
    return -1;
  }

  for (size_t i = 0; i < x.size(); ++i) {
    x[i] = std::log(clusterSize / x[i]);
    y[i] = std::log(y[i]);
    if (x[i] <= 0 || std::isinf(x[i]) ||
        y[i] <= 0 || std::isinf(y[i])) {
      x.erase(x.begin() + i);
      y.erase(y.begin() + i);
      --i;
    }
  }
  x.push_back(0);
  y.push_back(0);

  return normalEq2(x, y);
}

}; // namespace dendrite
