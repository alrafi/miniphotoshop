include "Processing.hpp"
#include <iostream>

    using namespace std;

static void Processing ::Processing(Image &image)
{
  int row = col = image.length for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      if ((image[i][j] > 142) && (image[i][j] < 250))
      {
        image[i][j] = 255;
      }
      else
      {
        image[i][j] = 0;
      }
    }
  }
};