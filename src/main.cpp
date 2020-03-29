#include <iostream>
#include "app.hpp"
#include "config.hpp"

int main(int argc, char *argv[])
{
  dendrite::Config config;
  config.parse(argc, argv);

  dendrite::App app(config);
  app.start();

  return 0;
}
