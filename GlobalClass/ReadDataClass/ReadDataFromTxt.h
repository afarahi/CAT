#ifndef __READDATAFROMTXT_H__
#define __READDATAFROMTXT_H__

#include "ReadDataClass.h"

class ReadDataFromTxt:public ReadDataClass{

   public:

     void readDataFromFile(string fname, 
                           Array2D< double > dataPoints,
                           int numColumns);

   private:

};

#endif
