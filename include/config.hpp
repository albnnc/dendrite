#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include "inipp.hpp"
#include "cxxopts.hpp"

namespace dendrite
{

class Config
{
public:
  Config();

  void parse(int argc, char *argv[]);

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
  std::string getExecutableDir();
};

}; // namespace dendrite
