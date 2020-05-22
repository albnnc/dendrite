#include "config.hpp"

namespace dendrite {

#ifdef _WIN32
#include <windows.h>
std::string Config::getExecutableDir() {
  char result[512];
  auto executablePath = std::string(
      result,
      GetModuleFileName(NULL, result, 512));
  return std::filesystem::path(executablePath).parent_path().string();
}
#endif

#ifdef __linux__
#include <unistd.h>
std::string Config::getExecutableDir() {
  char result[512];
  ssize_t count = readlink("/proc/self/exe", result, 512);
  auto executablePath = std::string(
      result,
      (count > 0) ? count : 0);
  return std::filesystem::path(executablePath).parent_path().string();
}
#endif

}; // namespace dendrite
