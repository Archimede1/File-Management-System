#include "File.h"
#include <iostream>
#include <string>
using namespace std;

File::File(){
  name = "";
  ext = "";
}

File::File(string ext){
  name = "";
  (*this).ext = ext;
}

File::File(string name, string ext){
  (*this).name = name;
  (*this).ext = ext;
}

File::~File(){
}

string File::getExt(){
  return ext;
}

string File::getName(){
  return name;
}