#include <iostream>
#include <string>
#include "File.h"
#include "SafeArray.h"
using namespace std;

#ifndef TEXTFILE_H
#define TEXTFILE_H

class TextFile : public File{
  private:
    SafeArray<int> characters;
    int charAmount;
    const static string ext;

  public:
    TextFile();
    TextFile(string fName);
    TextFile(SafeArray<int> characters, string fName);
    int getSize() const override;
    int getSizeByBits() const override;
    int getCharAmount();

};

#endif