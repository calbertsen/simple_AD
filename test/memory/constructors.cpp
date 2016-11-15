

#include <GrAD/GrAD>

int main(){

  using namespace GrAD;

  AD<double> a;
  AD<double> b(a);
  AD<double> c = b;
  AD<double> d(2.0);
  AD<double> e = 2.0;
  
  return 0;
}
