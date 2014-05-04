#include "LeastSquareFitClass.h"

void LeastSquareFitClass::nothing(MatrixXd A, VectorXd dataPoints){

   VectorXd b = A.adjoint() * dataPoints;
   MatrixXd M = A.adjoint() * A;

   //cout << "The matrix A is of size "
   //          << A.rows() << "x" << A.cols() << std::endl;
   //cout << "Here is the matrix b \n" << b << endl;
   //cout << "Here is the matrix M \n" << M << endl;

   // Solving M x = b 
   int n = b.size();
   VectorXd x(n);
   ConjugateGradient<MatrixXd> cg;
   cg.compute(M);
   x = cg.solve(b);
 
   //cout << "#iterations:     " << cg.iterations() << std::endl;
   //cout << "estimated error: " << cg.error()      << std::endl;
   //cout << "Final Result x = \n" << x << std::endl;

}


void LeastSquareFitClass::solveLeastSquareFit(MatrixXd A,
                                              VectorXd dataPoints,
                                              VectorXd *bestFit){

   VectorXd b = A.adjoint() * dataPoints;
   MatrixXd M = A.adjoint() * A;

   // Solving M x = b 
   ConjugateGradient<MatrixXd> cg;
   cg.compute(M);
   (*bestFit) = cg.solve(b);

}


void LeastSquareFitClass::make1dPolynomialMatrix(MatrixXd *P,
                                                 VectorXd x,
                                                 int polynomialDegree){

   P->resize(x.size(),polynomialDegree+1);   
   for (int iCol = 0; iCol < polynomialDegree+1; iCol++){
      for (int iRow = 0; iRow < x.size(); iRow++){
         (*P)(iRow,iCol) =  pow(x(iRow),iCol);
      }
   }

}
