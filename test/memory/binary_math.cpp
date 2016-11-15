

#include <GrAD/GrAD>

int main(){

  using namespace GrAD;

  AD<double> a(1.0);
  AD<double> b(4.0);
  AD<double> d(2.0);

  AD<double> z1 = a + b;
  AD<double> z2 = a - b;
  AD<double> z3 = a * b;
  AD<double> z4 = a / b;
  AD<double> z5 = z3 + z4 + AD<double>(-20);

  z1 += d;
  z2 *= d;
  z3 -= d;
  z4 /= d;
  z1 += AD<double>(2.0);
  z2 *= AD<double>(2.0);
  z3 -= AD<double>(2.0);
  z4 /= AD<double>(2.0);

  AD<double> q1 = atan2(b,d);
  AD<double> q2 = pow(b,d);
  AD<double> q3 = pow(b,2.0);
  
  return 0;
}
