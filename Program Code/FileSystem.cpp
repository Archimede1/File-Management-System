#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "TextFile.h"
#include "ImageFile.h"
#include "FileSystem.h"
using namespace std;

namespace FileSystemTools {
  void propOfFiles (const vector<File*>& file); 
  void propOfFilesRcrsn (vector<File*>& file); 
  vector<File*> filterOfFiles(const vector<File*>& file, string ext);
  void filterOfFilesRcrsn(vector<File*>& aVector, vector<File*>& destVector, string ext);
}

FileSystem::FileSystem(){}

void FileSystem::menu(){
 int input;
 cout << "Welcome to your File Management System. \nPlease choose one of the options: \n";
 cout << "Enter '1' to Read From a File.\n";
 cout << "Enter '2' to Create a New Image File.\n";
 cout << "Enter '3' to Create a New Text File\n";
 cout << "Enter '4' to Display All Files\n"; 
 cout << "Enter '5' to Display Image Files\n";
 cout << "Enter '6' to Display Text Files \n";
 cout << "Enter '7' to Delete a File \n";
 cout << "Enter '8' to Exit \n";
 input = intChecker();
 switch(input){
   default:
   case 1: readFile();
           break;
   case 2: newImageFile();
           break; 
   case 3: newTextFile();
           break;
   case 4: displayAllFiles();
           break;
   case 5: displayFiles("gif");
           break;
   case 6: displayFiles("txt");
           break; 
   case 7: {
     string fileExt, fileName;
     cout << "Enter File Name: ";
     getline(cin, fileName);
     cout << "Enter File Extension: ";
     getline (cin, fileExt);
     removeFile(fileName, fileExt);
     break;
   }
   case 8: cout << "Goodbye! \n";
           writeFile();
           return;   
 }
 cout << "PLEASE SELECT ENTER TO CONTINUE \n";
 cin.get();
 menu();
}

void FileSystem::newImageFile(){
  int width, height, colorDepth;
  string fileName;
  cout << "\nPlease Enter File Name: ";
  getline(cin, fileName);
  cout << "Please Enter Image Width: ";
  width = intChecker();
  cout << "Please Enter Image Height: ";
  height = intChecker();
  cout << "Please Enter Image Color Depth: ";
  colorDepth = intChecker();
  fileList.push_back(new ImageFile(fileName, width, height, colorDepth));
}

void FileSystem::newTextFile(){
	string fileName;
	cout << "\nPlease enter the file's name: ";
	getline (cin, fileName);
	fileList.push_back (new TextFile (fileName));
}

void FileSystem::removeFile(string name, string ext){
	int location = findFile(name, ext);
	if(location == NOT_FOUND) {
		cout << "The File Specified Could Not Be Found.\n";	
		return;
	}
	delete fileList[location];
	fileList.erase(fileList.begin() + location);
	cout << "\nThe File Specified Has Been Deleted\n\n";
}

int FileSystem::findFile(string name, string ext){
	name = convert(name);
	ext = convert(ext);
	for (int i = 0; i < fileList.size ( ); i++) {
		if (name == convert(fileList[i]->getName ( )) && ext == convert(fileList[i]->getExt ( ))) {
			return i;
		}
	}
	return NOT_FOUND;
}

void FileSystem::displayAllFiles( ){
	cout << "\n      File List\n";
	FileSystemTools::propOfFiles(fileList);
}

void FileSystem::displayFiles(string ext){
	cout << "\n      " + ext + " File List    \n";
	vector<File*> filesFound = FileSystemTools::filterOfFiles(fileList, ext);
	FileSystemTools::propOfFiles(filesFound);
}

void FileSystem::readFile(){
	cout << "\n    Reading From File   \n";
	int filesRead = 0;
	ifstream inputFile ("file.txt");
	if(inputFile.is_open()) {
		string inputLine;
		while(getline(inputFile, inputLine)) {
			if(inputLine == "txt") {
				string fileName;
				int fileSize;
				inputFile >> fileName >> fileSize;
				inputFile.ignore ( );
				fileList.push_back (new TextFile (SafeArray<int> (fileSize), fileName));
				filesRead++;
			} else if (inputLine == "gif") {
				string fileName;
				int height, width, colorDepth;
				inputFile >> fileName >> height;
				inputFile.get();
				inputFile.get();
				inputFile.get();
				inputFile >> width >> colorDepth;
				fileList.push_back (new ImageFile (fileName, height, width, colorDepth));
				inputFile.ignore ( );
				filesRead++;
			}
		}
	} else {
		cout << "Could not find file.txt\n";
	}
	cout << filesRead << " file" << (filesRead != 1 ? "s" : "");
	cout << " read\n";
}

void FileSystem::writeFile( ) const {
	ofstream outputFile ("file.txt");
	int numOfFiles = fileList.size ( );
	for (int i = 0; i < numOfFiles; ++i) {
		File* currentFile = fileList[i];
		outputFile << currentFile->getExt() << "\n" 
			<< currentFile->getName() << "\n";
		
		if(currentFile->getExt() == "gif") {
			ImageFile* anImageFile = dynamic_cast<ImageFile*>(currentFile);
			outputFile << anImageFile->getHeight ( ) << " x "
				<< anImageFile->getWidth ( ) << "\n"
				<< anImageFile->getColorDepth() << "\n";
		} else {
			outputFile << currentFile->getSizeByBits ( ) << "\n";
		}

		if(i != numOfFiles - 1) {
			outputFile << "\n";
		}
	}
	outputFile.close ( );
}

namespace FileSystemTools{
  void propOfFiles(const vector<File*>& file){
      vector<File*> temp(file);
      propOfFilesRcrsn(temp);
  }

  void propOfFilesRcrsn(vector<File*>& file){
    if(file.size() > 0){
      File* last = file.back();
      file.pop_back();
      propOfFiles(file);
      cout << "(Type): " << last->getExt() << "\n";
      cout << "(Name): " << last->getName() << "\n";
    if(last->getExt() == "gif"){
        ImageFile* otherImageFile = dynamic_cast<ImageFile*>(last);
        cout << "(Dimension): " << otherImageFile->getHeight() << " by " << otherImageFile->getWidth() << "\n";
      }
      cout << "(Size): " << last->getSize() << " bytes\n\n";
    }
  }

  vector<File*> filterOfFiles(const vector<File*>& file, string ext) {
    vector<File*> temp(file), filesToReturn;
    filterOfFilesRcrsn(temp, filesToReturn, ext);
    return filesToReturn;
  }

  void filterOfFilesRcrsn(vector<File*>& aVector, vector<File*>& destVector, string ext) {
    if (aVector.size() == 0) {
      return;
    }
    File* last = aVector.back();
    aVector.pop_back();
    filterOfFilesRcrsn(aVector, destVector, ext);
    if (last->getExt() == ext) {
      destVector.push_back(last);
    }
  }
}

bool FileSystem::yOrNChecker(){
  string result;
  getline(cin, result);
  while (convert(result) != "NO" && convert(result) != "YES" && result != "N" && result != "n" && result != "y"  && result != "Y" ){
      getline(cin, result);
    }
  switch(result[0]){
    case 'Y':
    case 'y': return true;
    case 'N':
    case 'n':
    default: return false;
  }
}

int FileSystem::intChecker(){
  int n;
  while(!(cin >> n)){
    cin.clear();
    cin.ignore(100, '\n');
    cout << endl;
  }
  cin.ignore();
  return n;
}

string FileSystem::convert(string data){
  for(int i = 0; i < data.length(); i++){
    data[i] = (char)(toupper(data[i]));
  }
  return data;
}



