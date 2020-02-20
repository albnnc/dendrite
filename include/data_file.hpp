#pragma once

#include <vector>
#include <fstream>
#include "vec2.hpp"

namespace dendrite
{

class DataFile
{
public:
  std::string title;
  std::vector<Vec2> data;

  DataFile(std::string title)
  {
    this->title = title;
  }

  void push(Vec2 v)
  {
    data.push_back(v);
  }

  void write(std::string path = "")
  {
    if (path.length() == 0)
    {
      path = title + ".dat";
    }
    std::ofstream out;
    out.open(path);
    for (auto it = data.begin(); it != data.end(); ++it)
    {
      out << it->x << "\t" << it->y << std::endl;
    }
    out << std::endl;
  }
};

}; // namespace dendrite
