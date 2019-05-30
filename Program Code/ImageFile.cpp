#include <iostream>
#include <string>
#include "ImageFile.h"
using namespace std;

const std::string ImageFile::ext = "gif";

ImageFile::ImageFile() : File(ext), pixelDimension(SafeMatrix<int>(0,0)), colorDepth(0){}

ImageFile::ImageFile(string fName, int width, int height, int depth): File(fName, ext),pixelDimension(SafeMatrix<int>(height, width)), colorDepth(depth){}

ImageFile::ImageFile(SafeMatrix<int> pixelDim, string fileName, int depth): File(fileName, ext), pixelDimension(pixelDim), colorDepth(depth){}

int ImageFile::getColorDepth(){
  return colorDepth;
}

int ImageFile::getHeight(){
  return pixelDimension.length();
}

int ImageFile::getWidth(){
  return pixelDimension[0].length();
}

int ImageFile::getSize( ) const{
	return static_cast<double>(pixelDimension.length() * pixelDimension.width() * colorDepth) / 8;
}

int ImageFile::getSizeByBits( ) const {
	return pixelDimension.length ( ) * pixelDimension.width ( );
}

