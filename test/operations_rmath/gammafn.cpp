
#include <GrAD/GrAD>
#include <GrAD/Rmath>

#include <cstdlib>
using std::vector;

vector<bool> gammafn_test(int seed){

  using namespace GrAD;
  using namespace GrAD::Rmath;

  vector<bool> rOut(2);
  
  
  srand(seed);
  double x0 = rand()/(double)RAND_MAX;

  double fnTrue = gammafn(x0);
  double grTrue = psigamma(x0,0.0) * gammafn(x0);

  vector<string> params(1);
  params[0] = "x";
  ADparlist<double>* grd = new ADparlist<double>(params);

  AD<double> x(x0,"x",grd);
  AD<double> z = gammafn(x);
  double fn = z.fn();
  double gr = z.gr()[0];

  
  bool feq = fabs(fn - fnTrue < 1e-16);
  bool greq = fabs(gr - grTrue < 1e-16);;

  rOut[0] = feq;
  rOut[1] = greq;
  
  return rOut;

}


int main(){
  vector<bool> r = gammafn_test(289734);
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
