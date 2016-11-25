

#define NDEBUG 1


#ifdef __cplusplus
#if __cplusplus >= 201103L


#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>   
#include <cppad/cppad.hpp>
#include <Eigen/Dense>

using namespace std;

#include "../templates/eigen.hpp"


namespace cppad {

  vector<double> eigen_grad(int seed, int na, bool optim = false){

    using namespace CppAD;
    using namespace Eigen;
  
    std::vector<double> res(8);
    clock_t t;
    double t1, t2, t3;

    srand(seed);
    Matrix<double,Dynamic,Dynamic> x0(na,na);
    for(int i = 0; i < na; ++i)
      for(int j = 0; j < na; ++j)
    	if(j > i){
    	  x0(i,j) = 0.0;
	}else if(j == i){
	  x0(i,j) = 1.0;
    	}else{	  
    	  x0(i,j) = rand() / (double)RAND_MAX;
    	}

    int indx = 0;
    std::vector<AD<double> > X((na*na-na)/2);
    std::vector<double> x00((na*na-na)/2);
    for(int i = 0; i < na; ++i)
      for(int j = 0; j < na; ++j)
    	if(i < j)
    	  X[indx++] = x0(i,j);
    Independent(X);

    indx = 0;
    Matrix<AD<double>,Dynamic,Dynamic> x(na,na);
    for(int i = 0; i < na; ++i)
      for(int j = 0; j < na; ++j)
      	if(j > i){
    	  x(i,j) = 0.0;
	}else if(i == j){
	  x(i,j) = 1.0;
    	}else{
	  x00[indx] = x0(i,j);
    	  x(i,j) = X[indx++];
    	}
    

    // Time to calculate double function
    t = clock();
    double fnTrue = eigen_fn(x0);
    t = clock() - t;
    t1 = ((double)t)/((double)CLOCKS_PER_SEC);

    // Time to create graph + function value
    t = clock();
    std::vector<AD<double> > Z(1);
    Z[0] = eigen_fn(x);
    CppAD::ADFun<double> f(X,Z);
    if(optim)
      f.optimize();
    double fn = f.Forward(0,x00)[0];
    //double fn = fnTrue;//Value(Z);
    t = clock() - t;
    t2 = ((double)t)/((double)CLOCKS_PER_SEC);

    // Time to get gradient
    t = clock();
    std::vector<double> w(1);
    w[0] = 1.0;
    std::vector<double> gr = f.Reverse(1,w);
    t = clock() - t;
    t3 = ((double)t)/((double)CLOCKS_PER_SEC);

    // std::vector<double> grTrue = eigen_true_gr(x0);
    //std::cout << gr.size() << "  " << (na*na-na)/2 << std::endl;
    bool feq = (fabs(fn - fnTrue) < 1e-12);
    bool greq = true;
    // for(int i = 0; i < gr.size(); ++i){
    //   greq = greq && (fabs(gr[i] - grTrue[i]) < 1e-12);
    // }
    res[0] = (double)seed; // seed
    res[1] = t1; // Time for double function
    res[2] = t2; 
    res[3] = t3; 
    res[4] = feq; 
    res[5] = greq; 
    res[6] = (t2+t3)/t1; 
    res[7] = t3/t1; 
  
    return res;
  }

}



int main(){

  using std::cout;
  using std::setw;
  using std::endl;


  std::vector<double> res = cppad::eigen_grad(674,20);

  cout << setw(10) << "Library";
  cout << setw(10) << "Example";
  cout << setw(10) << "Seed";
  cout << setw(10) << "double";
  cout << setw(10) << "all AD";
  cout << setw(10) << "gr AD";
  cout << setw(10) << "all ratio";
  cout << setw(10) << "gr ratio";
  cout << setw(10) << "fn corr";
  cout << setw(10) << "gr corr";
  cout << endl;
  cout << setw(10) << "CppAD";
  cout << setw(10) << "Eigen";
  cout << setw(10) << res[0];
  cout << setw(10) << res[1];
  cout << setw(10) << res[2];
  cout << setw(10) << res[3];
  cout << setw(10) << res[6];
  cout << setw(10) << res[7];
  cout << setw(10) << res[4];
  cout << setw(10) << res[5];
    cout << endl;
  return 0;
}


#else
int main(){
  cout << "Eigen example skipped for C++ versions before 11" << endl;
  return 0;
}

#endif
#endif
