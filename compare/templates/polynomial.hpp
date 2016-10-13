

template<class T>
T polynomial_fn(T x, vector<T> a){
  // T x0 = x;
  T res = a[0];
  for(int i = 1; i < a.size(); ++i){
    res += a[i] * pow(x,T(i));
    // res += a[i] * x0;
    // x0 *= x;
  }
  return res;
}

// Gradient of both a and x
vector<double> polynomial_true_gr(double x, vector<double> a){
  vector<double> r(a.size()+1);
  r[0] = 1.0;
  for(int i = 1; i < a.size(); ++i){
    r[i] = r[i-1] * x;
  }
  // w.r.t x
  double x0 = 1.0;
  int j = r.size()-1;
  for(int i = 1; i < a.size(); ++i){
    r[j] += i * x0 * a[i];
    x0 *= x;
  }
  return r;
}
