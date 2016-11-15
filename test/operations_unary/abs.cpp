
#include <GrAD/GrAD>
#include <cstdlib>
using std::vector;

vector<bool> abs_test(int seed){

  using namespace GrAD;

  vector<bool> rOut(2);
  
  
  srand(seed);
  double x0 = rand()/(double)RAND_MAX;

  double fnTrue = abs(x0);
  double grTrue = sign(x0);

  ADparlist<double>* grd = new ADparlist<double>();

  AD<double> x(x0);
  grd->Independent(x);
  AD<double> z = abs(x);
  double fn = z.fn();
  double gr = z.gr()[0];

  
  bool feq = fabs(fn - fnTrue < 1e-16);
  bool greq = fabs(gr - grTrue < 1e-16);;

  rOut[0] = feq;
  rOut[1] = greq;

  delete grd;
  return rOut;

}


int main(){
  vector<bool> r = abs_test(289734);
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
