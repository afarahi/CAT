#include "ReadDataFromTxt.h"

void ReadDataFromTxt::readDataFromFile(string fname, 
                                       Array2D< double > dataPoints,
                                       int numColumns){

   ifstream inFile;

   inFile.open(fname.c_str());
   string readLine;
   getline(inFile, readLine);

   cout << readLine << endl;

}

