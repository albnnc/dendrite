#pragma once

#include "cxxopts.hpp"
#include "inipp.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace dendrite {

class Config {
public:
  Config();

  void parse(int argc, char *argv[]);

  template <typename T>
  T get(std::string section, std::string variable) {
    T t;
    bool hasExtracted = inipp::extract<char, T>(ini.sections[section][variable], t);
    if (!hasExtracted) {
      std::cout << "Unable to find \""
                << section
                << "."
                << variable
                << "\" in config"
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
  std::string configPath = "";
};

}; // namespace dendrite
