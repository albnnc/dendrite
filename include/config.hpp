#pragma once

#include <iostream>
#include <fstream>
#include "inipp.hpp"

namespace dendrite
{

class Config
{
public:
  Config()
  {
  }

  void read()
  {
    std::ifstream ifs("config.ini");
    ini.parse(ifs);
  }

  template <typename T>
  T get(std::string section, std::string variable)
  {
    T t;
    bool hasExtracted = inipp::extract<char, T>(ini.sections[section][variable], t);
    if (!hasExtracted)
    {
      std::cout
          << "Unable to find \""
          << section
          << "."
          << variable
          << "\" in config.ini"
          << std::endl
          << "Aborting"
          << std::endl;
      exit(1);
    }
    return t;
  }

private:
  inipp::Ini<char> ini;
};

}; // namespace dendrite
