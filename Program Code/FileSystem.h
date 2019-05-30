#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "File.h"

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

class FileSystem{
  public:
    FileSystem();
    void menu();
  private:
    void newImageFile();
    void newTextFile();
    int findFile(string name, string ext);
    void removeFile (string name, string ext);
    void displayAllFiles();
    void displayFiles(string ext);
    void readFile();
    void writeFile() const;
    vector<File*> fileList;
    enum negAssignment{
      NOT_FOUND = -1
    };
    int intChecker();
    bool yOrNChecker();
    
    string convert(string data);
    
};

#endif