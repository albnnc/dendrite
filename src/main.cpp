#include <iostream>
#include "app.hpp"
#include "config.hpp"

int main()
{
  dendrite::Config config;
  config.read();

  dendrite::App app(config);
  app.start();

  return 0;
}
