#include <iostream>
#include <string>
using namespace std;

#ifndef FILE_H
#define FILE_H

class File{
  private:
    string name;
    string ext; //extension
  public:
    File();
    File(string ext);
    File(string name, string ext);
    virtual ~File();
    string getName();
    string getExt();
    virtual int getSize() const = 0;
    virtual int getSizeByBits() const = 0;
};

#endif