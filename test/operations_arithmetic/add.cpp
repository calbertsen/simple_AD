



double add_true_fn(int n, int seed){
  srand(seed);
  double res = 0.0;
  vector<double> x0(n);
  for(int i = 0; i < n; ++i){
    x0[i] = rand() / (double)RAND_MAX;
  }

  for(int i = 0; i < n; ++i){
    res += x0[i];
  }
  return res;
}

vector<double> add_true_gr(int n, int seed){
  srand(seed);
  vector<double> res(n);
  vector<double> x0(n);
  for(int i = 0; i < n; ++i){
    x0[i] = rand() / (double)RAND_MAX;
  }

  for(int i = 0; i < n; ++i){
    res[i] = 1.0;
  }
  return res;
}

bool add_test(int n, int seed){

  using namespace GrAD;
  
  srand(seed);
  AD<double> res = 0.0;
  ADparlist<double>* grd = new ADparlist<double>();

  vector<AD<double> > X(n);
  for(int i = 0; i < n; ++i)
    X[i] = AD<double>(rand()/(double)RAND_MAX);

  grd->Independent(X);
  
  vector<double> x0(n);
  for(int i = 0; i < n; ++i){
    x0[i] = 0.0;
  }


  clock_t t;
  float t1, t2, t3, t4;
  std::cout << "Evaluate double function:\nTime: ";
  t = clock();
  double fnt = add_true_fn(n,seed);
  t = clock() - t;
  t1 = ((float)t)/CLOCKS_PER_SEC;
  std::cout << t1 << " s.\n";
  vector<double> grt = add_true_gr(n,seed);

   
  std::cout << "Evaluate AD<double> function + gradient:\nTime: ";
  t = clock();
  for(int i = 0; i < n; ++i){
    res += X[i];
  }
  double fn = res.fn();
  vector<double> gr = res.gr();
  t = clock() - t;
  t2 = ((float)t)/CLOCKS_PER_SEC;
  std::cout << t2 << " s.\nRatio: " << t2/t1 << "\n";

  std::cout << "Evaluate forward AD<double> function + gradient:\nTime: ";
  t = clock();
  for(int i = 0; i < n; ++i){
    res += X[i];
  }
  double fnf = res.forward_fn(x0);
  vector<double> grf = res.forward_gr(x0);
  t = clock() - t;
  t2 = ((float)t)/CLOCKS_PER_SEC;
  std::cout << t2 << " s.\nRatio: " << t2/t1 << "\n";

  

  CppAD::vector<double> x0c(n);
  for(int i = 0; i < n; ++i)
    x0c[i] = X[i].root->getValue();
  CppAD::vector<double> w(1);
  w[0] = 1.0;
    

  CppAD::vector<CppAD::AD<double> > XC(n);
  for(int i = 0; i < n; ++i)
    XC[i] = x0[i];

  CppAD::Independent(XC);
  
  
  std::cout << "Evaluate CppAD::AD<double> reverse gradient:\nTime: ";
  t = clock();
  CppAD::vector<CppAD::AD<double> > Y(1);
  for(int i = 0; i < n; ++i)
    Y[0] += XC[i];
  CppAD::ADFun<double> f(XC,Y);
  CppAD::vector<double> gr1 = f.Reverse(1,w);
  t = clock() - t;
  t3 = ((float)t)/CLOCKS_PER_SEC;
  std::cout << t3 << " s.\nRatio: " << t3/t1 << "\n";


  
  bool feq = (fn - fnt < 1e-16);
  std::cout << "Correct function: " << feq << "\n";
  bool greq = true;
  for(int i = 0; i < n; ++i)
    greq = greq && (x0[i] - grt[i] < 1e-16);
  std::cout << "Correct derivative: " << greq << "\n";

  delete grd;
  return feq && greq;

}

