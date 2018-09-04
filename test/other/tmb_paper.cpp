
#include <GrAD/GrAD>
#include <cstdlib>

using namespace GrAD;


template<class T>
T tmb_paper_fn(vector<T> x){
  T res = pow(x[0],T(2.0)); //x[0]*x[0];
  for(int i = 1; (size_t)i < x.size(); ++i){
    res += pow((x[i] - x[i-1]),T(2.0));
    //res += (x[i] - x[i-1]) * (x[i] - x[i-1]);
  }
  return res;
}


// Gradient of both a and x
vector<double> tmb_paper_true_gr(vector<double> x){
  vector<double> r(x.size());

  r[0] = 4*x[0] - 2 * x[1];
  for(int i = 1; (size_t)i < x.size()-1; ++i)
    r[i] = -2.0*x[i+1] + 4.0 * x[i] - 2.0*x[i-1];
  r[x.size()-1] = 2*x[x.size()-1] - 2 * x[x.size()-2];
  
  return r;
}


vector<double> tmb_paper_grad(int seed, int na){

  
  vector<double> res(8);
  clock_t t;
  double t1, t2, t3;

  srand(seed);

  ADparlist<double>* grd = new ADparlist<double>();

  vector<double> x0(na);
  for(int i = 0; (size_t)i < x0.size(); ++i)
    x0[i] = rand() / (double)RAND_MAX;
    
  vector<AD<double> > x(na);
  for(int i = 0; i < na; ++i)
    x[i] = AD<double>(x0[i]);

  grd->Independent(x);

  // Time to calculate double function
t = clock();
  double fnTrue = tmb_paper_fn(x0);
  t = clock() - t;
  t1 = ((double)t)/((double)CLOCKS_PER_SEC);

  // Time to create graph + function value
  t = clock();
  AD<double> z = tmb_paper_fn(x);
  double fn = z.fn();
  t = clock() - t;
  t2 = ((double)t)/((double)CLOCKS_PER_SEC);

  // Time to get gradient
  t = clock();
  vector<double> gr = z.gr();
  t = clock() - t;
  t3 = ((double)t)/((double)CLOCKS_PER_SEC);

  vector<double> grTrue = tmb_paper_true_gr(x0);

  bool feq = (fabs(fn - fnTrue) < 1e-12);
  bool greq = true;
  for(int i = 0; (size_t)i < gr.size(); ++i){
    greq = greq && (fabs(gr[i] - grTrue[i]) < 1e-12);
  }
  res[0] = (double)seed; // seed
  res[1] = t1; // Time for double function
  res[2] = t2; 
  res[3] = t3; 
  res[4] = feq; 
  res[5] = greq; 
  res[6] = (t2+t3)/t1; 
  res[7] = t3/t1; 

  delete grd;
  return res;
}

int main(){
  vector<double> r = tmb_paper_grad(836, 8000);
  if(r[4] && r[5]){
    return 0;
  }else if(r[4] && !r[5]){
    return 1;
  }else if(!r[4] && r[5]){
    return 2;
  }else{
    return 3;
  }
}
