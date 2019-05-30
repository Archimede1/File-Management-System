#include <iostream>
#include <string>
#include "TextFile.h"
using namespace std;

const std::string TextFile::ext= "txt";

TextFile::TextFile(): File(ext) {
  characters = SafeArray<int>(0);
  charAmount = 0;
}

TextFile::TextFile(string fName):  File(fName, ext){
  characters = SafeArray<int>(0);
  charAmount = 0;
}

TextFile::TextFile(SafeArray<int> characters, string fName): File(fName, ext){
  (*this).characters = characters;
  charAmount = characters.length();
}

int TextFile::getSize() const{
  return charAmount / 8;
}

int TextFile::getSizeByBits( ) const {
	return charAmount;
}

int TextFile::getCharAmount(){
  return charAmount;
}