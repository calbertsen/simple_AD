
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>   
#include <GrAD/GrAD>

using namespace std;

#include "../templates/simple.hpp"

namespace grad {

  vector<double> simple_grad(int seed){

    using namespace GrAD;
  
    vector<double> res(8);
    clock_t t;
    double t1, t2, t3;

    srand(seed);

    ADparlist<double>* grd = new ADparlist<double>();

    vector<double> x0(2);
    x0[0] = rand() / (double)RAND_MAX;
    x0[1] = rand() / (double)RAND_MAX;
  
    AD<double> x(x0[0]);
    AD<double> y(x0[1]);

    grd->Independent(x);
    grd->Independent(y);

    // Time to calculate double function
    t = clock();
    double fnTrue = simple_fn(x0[0],x0[1]);
    t = clock() - t;
    t1 = ((double)t)/((double)CLOCKS_PER_SEC);

    // // Time to create graph + function value
    t = clock();
    AD<double> p(2.0);
    AD<double> z = simple_fn(x,y);
    double fn = z.fn();
    t = clock() - t;
    t2 = ((double)t)/((double)CLOCKS_PER_SEC);

    // Time to get gradient
    t = clock();
    vector<double> gr = z.gr();
    t = clock() - t;
    t3 = ((double)t)/((double)CLOCKS_PER_SEC);

    vector<double> grTrue = simple_true_gr(x0[0],x0[1]);

    bool feq = (fabs(fn - fnTrue) < 1e-16);
    bool greq = true;
    for(int i = 0; i < gr.size(); ++i)
      greq = greq && (fabs(gr[i] - grTrue[i]) < 1e-16);

    res[0] = (double)seed; // seed
    res[1] = t1; // Time for double function
    res[2] = t2; 
    res[3] = t3; 
    res[4] = feq; 
    res[5] = greq; 
    res[6] = (t2+t3)/t1; 
    res[7] = t3/t1; 

    delete grd;
    return res;
  }

}



int main(){

  using std::cout;
  using std::setw;
  using std::endl;


  std::vector<double> res = grad::simple_grad(674);

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
  cout << setw(10) << "GrAD";
  cout << setw(10) << "Simple";
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
