#ifndef __LEASTSQUAREFIT_CLASS_H__
#define __LEASTSQUAREFIT_CLASS_H__


#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <Eigen/SparseCholesky>
#include <Eigen/SparseLU> 
#include <Eigen/SparseQR>
#include <Eigen/IterativeLinearSolvers>
#include <Eigen/Sparse>

using namespace Eigen;

class LeastSquareFitClass{

   public:

     void nothing(MatrixXd A,VectorXd x);

     // This function makes the polynomial degree on N
     // where the points defined in vector x and N = x.size()
     // polynomialDegree is degree of polynomial
     // It return resized matrix P(x.size(),polynomialDegree)
     void make1dPolynomialMatrix(MatrixXd *P, VectorXd x, int polynomialDegree);

     void solveLeastSquareFit(MatrixXd A,
                              VectorXd dataPoints,
                              VectorXd *bestFit);

   private:

};

#endif
