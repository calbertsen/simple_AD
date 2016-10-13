
#ifdef __cplusplus
#if __cplusplus >= 201103L

#include <GrAD/GrAD>
#include <cstdlib>
#include <iostream>

using std::vector;

vector<bool> expm1_test(int seed){

  using namespace GrAD;

  vector<bool> rOut(2);
  
  
  srand(seed);
  // Must be between -Inf and Inf
  double x0 = rand()/(double)RAND_MAX;

  double fnTrue = expm1(x0);
  double grTrue = exp(x0);

  vector<string> params(1);
  params[0] = "x";
  ADparlist<double>* grd = new ADparlist<double>(params);

  AD<double> x(x0,"x",grd);
  AD<double> z = expm1(x);
  double fn = z.fn();
  double gr = z.gr()[0];

  bool feq = fabs(fn - fnTrue < 1e-16);
  bool greq = fabs(gr - grTrue < 1e-16);

  rOut[0] = feq;
  rOut[1] = greq;
  
  return rOut;

}


int main(){

  vector<bool> r = expm1_test(289734);
  if(r[0] & r[1]){
    return 0;
  }else if(r[0] && !r[1]){
    return 1;
  }else if(!r[0] && r[1]){
    return 2;
  }else{
    return 3;
  }
}


#else

int main(){
  return 0;
}

#endif
#endif
