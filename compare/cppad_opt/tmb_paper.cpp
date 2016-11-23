
#ifdef __cplusplus
#if __cplusplus >= 201103L


#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>   
#include <cppad/cppad.hpp>

using namespace std;

#include "../templates/tmb_paper.hpp"


namespace cppad {

  vector<double> tmb_paper_grad(int seed, int na, bool optim = false){

    using namespace CppAD;
  
    std::vector<double> res(8);
    clock_t t;
    double t1, t2, t3;

    srand(seed);

    std::vector<double> x0(na);
    for(int i = 0; i < x0.size(); ++i)
      x0[i] = rand() / (double)RAND_MAX;

    std::vector<AD<double> > X(na);
    for(int i = 0; i < na; ++i){
      X[i] = x0[i];
    }

    Independent(X);
    

    // Time to calculate double function
    t = clock();
    double fnTrue = tmb_paper_fn(x0);
    t = clock() - t;
    t1 = ((double)t)/((double)CLOCKS_PER_SEC);

    // Time to create graph + function value
    t = clock();
    std::vector<AD<double> > Z(1);
    Z[0] = tmb_paper_fn(X);
    CppAD::ADFun<double> f(X,Z);
    if(optim)
      f.optimize();
    double fn = f.Forward(0,x0)[0];
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

    std::vector<double> grTrue = tmb_paper_true_gr(x0);

    bool feq = (fabs(fn - fnTrue) < 1e-12);
    bool greq = true;
    for(int i = 0; i < gr.size(); ++i){
      greq = greq && (fabs(gr[i] - grTrue[i]) < 1e-12);
    }
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


  std::vector<double> res = cppad::tmb_paper_grad(674,800);

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
  cout << setw(10) << "TMBpap";
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
  cout << "TMB paper example skipped for C++ versions before 11" << endl;
  return 0;
}

#endif
#endif
