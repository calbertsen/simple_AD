


#include <GrAD/GrAD>

int main(){

  using namespace GrAD;

  AD<double> c(2.0);
  AD<double> x(2.0);

  ADparlist<double> grd;
  grd.Independent(x);
  
  AD<double> a1, a2;

  a1 = abs(c);
  a2 = abs(x);

  a1 = acos(c);
  a2 = acos(x);

  a1 = asin(c);
  a2 = asin(x);

  a1 = atan(c);
  a2 = atan(x);

  a1 = cos(c);
  a2 = cos(x);

  a1 = cosh(c);
  a2 = cosh(x);

  a1 = exp(c);
  a2 = exp(x);

  a1 = fabs(c);
  a2 = fabs(x);

  a1 = log(c);
  a2 = log(x);

  a1 = log10(c);
  a2 = log10(x);

  a1 = sign(c);
  a2 = sign(x);

  a1 = sin(c);
  a2 = sin(x);

  a1 = sinh(c);
  a2 = sinh(x);

  a1 = sqrt(c);
  a2 = sqrt(x);

  a1 = tan(c);
  a2 = tan(x);

  a1 = tanh(c);
  a2 = tanh(x);


#ifdef __cplusplus
#if __cplusplus >= 201103L

  a1 = acosh(c);
  a2 = acosh(x);

  a1 = asinh(c);
  a2 = asinh(x);

  a1 = atanh(c);
  a2 = atanh(x);

  a1 = erf(c);
  a2 = erf(x);

  a1 = exp2(c);
  a2 = exp2(x);

  a1 = expm1(c);
  a2 = expm1(x);

  a1 = log2(c);
  a2 = log2(x);

  a1 = log1p(c);
  a2 = log1p(x);

#endif
#endif
  
  return 0;
}
