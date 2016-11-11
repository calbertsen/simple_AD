
#include <GrAD/GrAD>
#include <GrAD/Rmath>

#include <cstdlib>
using std::vector;

vector<bool> psigamma2_test(int seed){

  using namespace GrAD;
  using namespace GrAD::Rmath;

  vector<bool> rOut(2);
  
  
  srand(seed);
  double x0 = rand()/(double)RAND_MAX;

  double fnTrue = psigamma(x0,2.0);
  double grTrue = psigamma(x0,3.0);

  ADparlist<double>* grd = new ADparlist<double>();

  AD<double> x(x0);
  AD<double> z = psigamma(x,2.0);
  double fn = z.fn();
  double gr = z.gr()[0];

  
  bool feq = fabs(fn - fnTrue < 1e-16);
  bool greq = fabs(gr - grTrue < 1e-16);;

  rOut[0] = feq;
  rOut[1] = greq;
  
  return rOut;

}


int main(){
  vector<bool> r = psigamma2_test(289734);
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
