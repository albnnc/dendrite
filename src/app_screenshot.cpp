#include "app.hpp"

namespace dendrite
{

void App::screenshot()
{
  int frozenCount = 0;

  for (int i = 0; i < field.fieldSize; ++i)
  {
    for (int j = 0; j < field.fieldSize; ++j)
    {
      for (int k = 0; k < field.populationMax; ++k)
      {
        if (field.data[i][j][k].bornStep < 0)
        {
          break;
        }
        if (field.data[i][j][k].freezeStep > 0)
        {
          ++frozenCount;
        }
      }
    }
  }

  std::string path = "";
  path += outDir + "/dendrite_" + std::to_string(frozenCount) + ".png";
  sf::Texture texture;
  texture.create(window.getSize().x, window.getSize().y);
  texture.update(window);
  if (texture.copyToImage().saveToFile(path))
  {
    // success
  }
}

}; // namespace dendrite
