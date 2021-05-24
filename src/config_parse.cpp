#include "config.hpp"

namespace dendrite {

void Config::parse(int argc, char *argv[]) {
  try {
    cxxopts::Options options(argv[0]);
    options.add_options()(
        "c,config",
        "Specify path to config",
        cxxopts::value<std::string>());
    options.add_options()(
        "l,load",
        "Start in headless mode",
        cxxopts::value<std::string>());
    options.add_options()(
        "s,headless",
        "Start in headless mode",
        cxxopts::value<bool>());
    options.add_options()("h,help", "Show help");
    auto parsed = options.parse(argc, argv);

    if (parsed.count("help")) {
      std::cout << options.help({""}) << std::endl;
      exit(0);
    }

    std::string cwd = std::filesystem::current_path().u8string();
    if (parsed.count("config")) {
      std::string path = parsed["config"].as<std::string>();
      configPath = (std::filesystem::path(cwd) / path).string();
    } else {
      configPath = (std::filesystem::path(getExecutableDir()) / "config.ini").u8string();
    }

    std::cout << "Looking for config at \""
              << configPath
              << "\""
              << std::endl;
    std::ifstream ifs(configPath);
    ini.parse(ifs);

    ini.sections["common"]["isHeadless"] = parsed.count("headless") ? "true" : "false";
    if (parsed.count("load")) {
      ini.sections["common"]["hasToLoad"] = "true";
      std::string dumpToLoad = (std::filesystem::path(cwd) / parsed["load"].as<std::string>()).string();
      ini.sections["common"]["dumpToLoad"] = dumpToLoad;
    } else {
      ini.sections["common"]["hasToLoad"] = "false";
      ini.sections["common"]["dumpToLoad"] = "_";
    }

    ini.default_section(ini.sections["common"]);
    ini.interpolate();
  } catch (const cxxopts::OptionException &e) {
    std::cout << "Error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}

}; // namespace dendrite
