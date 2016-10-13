
#include <iostream>
#include <vector>
#include <ctime>
#include <GrAD/GrAD>
#include <cppad/cppad.hpp>
#include <Eigen/Dense>

using std::vector;

// Simple example
#include "templates/simple.hpp"
#include "grad/simple.cpp"
#include "cppad/simple.cpp"



#ifdef __cplusplus
#if __cplusplus >= 201103L
// Polynomial example
#include "templates/polynomial.hpp"
#include "grad/polynomial.cpp"
#include "cppad/polynomial.cpp"
#endif
#endif


#ifdef __cplusplus
#if __cplusplus >= 201103L
// TMB paper example
#include "templates/tmb_paper.hpp"
#include "grad/tmb_paper.cpp"
#include "cppad/tmb_paper.cpp"
#endif
#endif

#ifdef __cplusplus
#if __cplusplus >= 201103L
// Eigen example
#include "templates/eigen.hpp"
#include "grad/eigen.cpp"
#include "cppad/eigen.cpp"
#endif
#endif


int main(){

  using std::cout;
  using std::setw;
  using std::endl;

  cout << endl << endl << "Comparing GrAD to other AD libraries" <<endl<<endl;
  
  std::cout << "Running simple example...\n";

  vector<double> rsimple = grad::simple_grad(123);
  vector<double> csimple = cppad::simple_grad(123);
  vector<double> csimpleO = cppad::simple_grad(123,true);
  cout << setw(10) << "";
  cout << setw(10) << "GrAD";
  cout << setw(10) << "CppAD";
  cout << setw(10) << "CppADopt";
  cout << endl;
  cout << setw(10) << "Seed";
  cout << setw(10) << rsimple[0];
  cout << setw(10) << csimple[0];
  cout << setw(10) << csimpleO[0];
  cout << endl << setw(10) << "double";
  cout << setw(10) << rsimple[1];
  cout << setw(10) << csimple[1];
  cout << setw(10) << csimpleO[1];
  cout << endl <<  setw(10) << "all AD";
  cout << setw(10) << rsimple[2];
  cout << setw(10) << csimple[2];
  cout << setw(10) << csimpleO[2];
  cout <<  endl << setw(10) << "gr AD";
  cout  << setw(10) << rsimple[3];
  cout << setw(10) << csimple[3];
  cout << setw(10) << csimpleO[3];
  cout << endl <<  setw(10) << "all ratio";
  cout  << setw(10) << rsimple[6];
  cout << setw(10) << csimple[6];
  cout << setw(10) << csimpleO[6];
  cout << endl <<  setw(10) << "gr ratio";
  cout  << setw(10) << rsimple[7];
  cout << setw(10) << csimple[7];
  cout << setw(10) << csimpleO[7];
  cout << endl <<  setw(10) << "fn corr";
  cout  << setw(10) << rsimple[4];
  cout << setw(10) << csimple[4];
  cout << setw(10) << csimpleO[4];
  cout << endl <<  setw(10) << "gr corr";
  cout  << setw(10) << rsimple[5];
  cout << setw(10) << csimple[5];
  cout << setw(10) << csimpleO[5];
  cout << endl << endl;



#ifdef __cplusplus
#if __cplusplus >= 201103L
  std::cout << "Running polynomial example (na=2000)...\n";

  rsimple = grad::polynomial_grad(456,2000);
  csimple = cppad::polynomial_grad(456,2000);
  csimpleO = cppad::polynomial_grad(456,2000,true);
  cout << setw(10) << "";
  cout << setw(10) << "GrAD";
  cout << setw(10) << "CppAD";
  cout << setw(10) << "CppADopt";
  cout << endl;
  cout << setw(10) << "Seed";
  cout << setw(10) << rsimple[0];
  cout << setw(10) << csimple[0];
  cout << setw(10) << csimpleO[0];
  cout << endl << setw(10) << "double";
  cout << setw(10) << rsimple[1];
  cout << setw(10) << csimple[1];
  cout << setw(10) << csimpleO[1];
  cout << endl <<  setw(10) << "all AD";
  cout << setw(10) << rsimple[2];
  cout << setw(10) << csimple[2];
  cout << setw(10) << csimpleO[2];
  cout <<  endl << setw(10) << "gr AD";
  cout  << setw(10) << rsimple[3];
  cout << setw(10) << csimple[3];
  cout << setw(10) << csimpleO[3];
  cout << endl <<  setw(10) << "all ratio";
  cout  << setw(10) << rsimple[6];
  cout << setw(10) << csimple[6];
  cout << setw(10) << csimpleO[6];
  cout << endl <<  setw(10) << "gr ratio";
  cout  << setw(10) << rsimple[7];
  cout << setw(10) << csimple[7];
  cout << setw(10) << csimpleO[7];
  cout << endl <<  setw(10) << "fn corr";
  cout  << setw(10) << rsimple[4];
  cout << setw(10) << csimple[4];
  cout << setw(10) << csimpleO[4];
  cout << endl <<  setw(10) << "gr corr";
  cout  << setw(10) << rsimple[5];
  cout << setw(10) << csimple[5];
  cout << setw(10) << csimpleO[5];
  cout << endl << endl;
#else
  cout << "Polynomial example skipped for C++ versions before 11" << endl;
#endif
#endif

#ifdef __cplusplus
#if __cplusplus >= 201103L
  std::cout << "Running TMB paper example (na=8000)...\n";

  rsimple = grad::tmb_paper_grad(67124,8000);
  csimple = cppad::tmb_paper_grad(67124,8000);
  csimpleO = cppad::tmb_paper_grad(67124,8000,true);
  cout << setw(10) << "";
  cout << setw(10) << "GrAD";
  cout << setw(10) << "CppAD";
  cout << setw(10) << "CppADopt";
  cout << endl;
  cout << setw(10) << "Seed";
  cout << setw(10) << rsimple[0];
  cout << setw(10) << csimple[0];
  cout << setw(10) << csimpleO[0];
  cout << endl << setw(10) << "double";
  cout << setw(10) << rsimple[1];
  cout << setw(10) << csimple[1];
  cout << setw(10) << csimpleO[1];
  cout << endl <<  setw(10) << "all AD";
  cout << setw(10) << rsimple[2];
  cout << setw(10) << csimple[2];
  cout << setw(10) << csimpleO[2];
  cout <<  endl << setw(10) << "gr AD";
  cout  << setw(10) << rsimple[3];
  cout << setw(10) << csimple[3];
  cout << setw(10) << csimpleO[3];
  cout << endl <<  setw(10) << "all ratio";
  cout  << setw(10) << rsimple[6];
  cout << setw(10) << csimple[6];
  cout << setw(10) << csimpleO[6];
  cout << endl <<  setw(10) << "gr ratio";
  cout  << setw(10) << rsimple[7];
  cout << setw(10) << csimple[7];
  cout << setw(10) << csimpleO[7];
  cout << endl <<  setw(10) << "fn corr";
  cout  << setw(10) << rsimple[4];
  cout << setw(10) << csimple[4];
  cout << setw(10) << csimpleO[4];
  cout << endl <<  setw(10) << "gr corr";
  cout  << setw(10) << rsimple[5];
  cout << setw(10) << csimple[5];
  cout << setw(10) << csimpleO[5];
  cout << endl << endl;
#else
  cout << "TMB paper example skipped for C++ versions before 11" << endl;
#endif
#endif



#ifdef __cplusplus
#if __cplusplus >= 201103L
  std::cout << "Running Eigen example - trace of A * A^T (na=200)...\n";

  rsimple = grad::eigen_grad(674,200);
  csimple = cppad::eigen_grad(674,200);
  csimpleO = cppad::eigen_grad(674,200,true);
  cout << setw(10) << "";
  cout << setw(10) << "GrAD";
  cout << setw(10) << "CppAD";
  cout << setw(10) << "CppADopt";
  cout << endl;
  cout << setw(10) << "Seed";
  cout << setw(10) << rsimple[0];
  cout << setw(10) << csimple[0];
  cout << setw(10) << csimpleO[0];
  cout << endl << setw(10) << "double";
  cout << setw(10) << rsimple[1];
  cout << setw(10) << csimple[1];
  cout << setw(10) << csimpleO[1];
  cout << endl <<  setw(10) << "all AD";
  cout << setw(10) << rsimple[2];
  cout << setw(10) << csimple[2];
  cout << setw(10) << csimpleO[2];
  cout <<  endl << setw(10) << "gr AD";
  cout  << setw(10) << rsimple[3];
  cout << setw(10) << csimple[3];
  cout << setw(10) << csimpleO[3];
  cout << endl <<  setw(10) << "all ratio";
  cout  << setw(10) << rsimple[6];
  cout << setw(10) << csimple[6];
  cout << setw(10) << csimpleO[6];
  cout << endl <<  setw(10) << "gr ratio";
  cout  << setw(10) << rsimple[7];
  cout << setw(10) << csimple[7];
  cout << setw(10) << csimpleO[7];
  cout << endl <<  setw(10) << "fn corr";
  cout  << setw(10) << rsimple[4];
  cout << setw(10) << csimple[4];
  cout << setw(10) << csimpleO[4];
  cout << endl <<  setw(10) << "gr corr";
  cout  << setw(10) << rsimple[5];
  cout << setw(10) << csimple[5];
  cout << setw(10) << csimpleO[5];
  cout << endl << endl;
#else
  cout << "Eigen example skipped for C++ versions before 11" << endl;
#endif
#endif



  cout << endl << endl;
  
  return 0;
}
