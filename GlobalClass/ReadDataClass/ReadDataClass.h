#ifndef __READDATA_CLASS_TEMP_H__
#define __READDATA_CLASS_TEMP_H__


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "../../LinearAlgebraTools/TNT/tnt.h"
using namespace TNT;


// This is the abstract class for reading data from input file
class ReadDataClass{

   public:

     virtual void readDataFromFile(string fname, 
                                   Array2D< double > dataPoints,
                                   int numColumns) = 0;

   private:

};

#include "ReadDataFromTxt.h"
//#include "InitialConditionClass_Step.h"
//#include "InitialConditionClass_RndNoise.h"

#endif
