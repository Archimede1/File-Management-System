#ifndef SAFE_MATRIX_H
#define SAFE_MATRIX_H

#include "SafeArray.h"
#include <iostream>
#include <iosfwd>
using namespace std;

template<class T>
class SafeMatrix{
  public:
    SafeMatrix(int rows, int columns);
    void tester();
    int length() const;
    int width() const;
    SafeArray<T>& operator[](int index);

  private:
    int rowSize;
    SafeArray<SafeArray<T> > theRows;
};

template<class T>
SafeMatrix<T>::SafeMatrix(int rows, int columns) : rowSize(rows), theRows(SafeArray<SafeArray<T> >(rowSize)) {
  for(int i = 0; i < rowSize; i++){
    theRows[i] = SafeArray<T>(columns);
  }
}

template<class T>
void SafeMatrix<T>::tester(){
  int r, c, result;
  cout << "\nTesting length() Method \nTest 1 \n";
  cout << "Dimesions for This Matrix: \n";
  cout << "(*this).length(): " << (*this).length() << endl;
  cout << "(*this)[0].length(): " << (*this)[0].length() << endl;
  cout << endl;

  cout << "Testing '[]' operator \nTest 2 \n";
  cout << "Enter Row Number: ";
  cin >> r;
  cout << "Enter Column Number: ";
  cin >> c;
  cout << "Choose an Value for [r][c]: ";
  cin >> result;
  (*this)[r][c] = result;
  cout << "matrix[" << r  << "][" << c << "] has been set to " << result << "\n";
  cout << "Select Print To Check! \n";
  cout << endl;
}

template<class T>
int SafeMatrix<T>::length()const{
  return rowSize;
}

template<class T>
SafeArray<T>& SafeMatrix<T>::operator[](int index){
  return theRows[index];
}


template <class T>
int SafeMatrix<T>::width() const{
	if(rowSize == 0) {
		return 0;
	}
	return theRows[0].length();
}

#endif
