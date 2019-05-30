#include <iostream>
#include <string>
#include "File.h"
#include "SafeMatrix.h"
using namespace std;

#ifndef IMAGEFILE_H
#define IMAGEFILE_H

class ImageFile : public File{
  private:
    SafeMatrix<int> pixelDimension;
    int colorDepth;
    const static string ext;
  
  public:
    ImageFile();
    ImageFile(string fName, int width, int height, int depth);
    ImageFile(SafeMatrix<int> pixelDim, string fileName, int depth);
    int getColorDepth();
    int getHeight();
    int getWidth();
    int getSize() const override;
    int getSizeByBits() const override;

};

#endif