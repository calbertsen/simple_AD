

#include <GrAD/GrAD>

int main(){

  using namespace GrAD;

  AD<double> d(2.0);
  AD<double> e = 2.0;

  ADparlist<double> grd;
  grd.Independent(e);
  grd.Independent(d);
  
  return 0;
}
