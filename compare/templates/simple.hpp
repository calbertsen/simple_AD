
template<class T>
T simple_fn(T x,T y){
  return exp(-pow(x,T(2.0))/y) + y;
}

vector<double> simple_true_gr(double x, double y){
  vector<double> r(2);
  r[0] = -2.0 * x * exp(-pow(x,2.0)/y) / y;
  r[1] = pow(x,2.0) * exp(- pow(x,2.0)/y) / pow(y,2.0) + 1.0;
  return r;
}
