#include "config.hpp"

namespace dendrite
{

void Config::parse(int argc, char *argv[])
{
  try
  {
    std::string configPath = "";

    cxxopts::Options options(argv[0]);
    options.add_options()(
        "c,config",
        "Specify path to config",
        cxxopts::value<std::string>());
    options.add_options()("h,help", "Show help");
    auto parsed = options.parse(argc, argv);

    if (parsed.count("help"))
    {
      std::cout << options.help({""}) << std::endl;
      exit(0);
    }

    if (parsed.count("config"))
    {
      std::string cwd = std::filesystem::current_path();
      std::string path = parsed["config"].as<std::string>();
      configPath = (std::filesystem::path(cwd) / path).string();
    }
    else
    {
      configPath = std::filesystem::path(getExecutableDir()) / "config.ini";
    }

    std::cout << "Looking for config at \""
              << configPath
              << "\""
              << std::endl;
    std::ifstream ifs(configPath);
    ini.parse(ifs);
  }
  catch (const cxxopts::OptionException &e)
  {
    std::cout << "Error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}

}; // namespace dendrite