

template<class T>
T tmb_paper_fn(vector<T> x){
  T res = pow(x[0],T(2.0)); //x[0]*x[0];
  for(int i = 1; i < x.size(); ++i){
    res += pow((x[i] - x[i-1]),T(2.0));
    //res += (x[i] - x[i-1]) * (x[i] - x[i-1]);
  }
  return res;
}


// Gradient of both a and x
vector<double> tmb_paper_true_gr(vector<double> x){
  vector<double> r(x.size());

  r[0] = 4*x[0] - 2 * x[1];
  for(int i = 1; i < x.size()-1; ++i)
    r[i] = -2.0*x[i+1] + 4.0 * x[i] - 2.0*x[i-1];
  r[x.size()-1] = 2*x[x.size()-1] - 2 * x[x.size()-2];
  
  return r;
}
