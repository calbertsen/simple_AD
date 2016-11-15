
namespace grad {

  vector<double> polynomial_grad(int seed, int na){

    using namespace GrAD;
  
    vector<double> res(8);
    clock_t t;
    double t1, t2, t3;

    srand(seed);

    ADparlist<double>* grd = new ADparlist<double>();

    vector<double> a0(na);
    for(int i = 0; i < a0.size(); ++i)
      a0[i] = rand() / (double)RAND_MAX;
    double x0 = rand() / (double)RAND_MAX;
    std::cout << a0[0] << "  " << a0[1] << "  " << x0 <<"\n";

    vector<AD<double> > a(na);
    for(int i = 0; i < na; ++i){
      a[i] = AD<double>(a0[i]);
    }
    
    AD<double> x(x0);

    grd->Independent(a);
    grd->Independent(x);
    
    // Time to calculate double function
    t = clock();
    double fnTrue = polynomial_fn(x0,a0);
    t = clock() - t;
    t1 = ((double)t)/((double)CLOCKS_PER_SEC);

    // Time to create graph + function value
    t = clock();
    AD<double> z = polynomial_fn(x,a);
    double fn = z.fn();
    t = clock() - t;
    t2 = ((double)t)/((double)CLOCKS_PER_SEC);

    // Time to get gradient
    t = clock();
    vector<double> gr = z.gr();
    t = clock() - t;
    t3 = ((double)t)/((double)CLOCKS_PER_SEC);

    vector<double> grTrue = polynomial_true_gr(x0,a0);

    bool feq = (fabs(fn - fnTrue) < 1e-16);
    bool greq = true;
    for(int i = 0; i < gr.size(); ++i)
      greq = greq && (fabs(gr[i] - grTrue[i]) < 1e-16);

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

}
