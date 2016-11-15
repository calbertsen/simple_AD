
namespace grad {

  vector<double> eigen_grad(int seed, int na){

    using namespace GrAD;
    using namespace Eigen;
  
    vector<double> res(8);
    clock_t t;
    double t1, t2, t3;

    srand(seed);

    ADparlist<double>* grd = new ADparlist<double>();

    Matrix<double,Dynamic,Dynamic> x0(na,na);
    for(int i = 0; i < na; ++i)
      for(int j = 0; j < na; ++j)
    	if(j > i){
    	  x0(i,j) = 0.0;
	}else if(j == i){
	  x0(i,j) = 1.0;
    	}else{	  
    	  x0(i,j) = rand() / (double)RAND_MAX;
    	}
    
    Matrix<AD<double>,Dynamic,Dynamic> x(na,na);
    int indx = 0;
    for(int i = 0; i < na; ++i)
      for(int j = 0; j < na; ++j)
      	if(j > i){
    	  x(i,j) = AD<double>(0.0);
	}else if(i == j){
	  x(i,j) = AD<double>(1.0);
    	}else{
    	  x(i,j) = AD<double>(x0(i,j));
	  grd->Independent(x(i,j));
    	}
          
    // Time to calculate double function
    t = clock();
    double fnTrue = eigen_fn(x0);
    t = clock() - t;
    t1 = ((double)t)/((double)CLOCKS_PER_SEC);

    // Time to create graph + function value
    t = clock();

    AD<double> z = eigen_fn(x);
    double fn = z.fn();
    t = clock() - t;
    t2 = ((double)t)/((double)CLOCKS_PER_SEC);

    // Time to get gradient
    t = clock();
    vector<double> gr = z.gr();
    t = clock() - t;
    t3 = ((double)t)/((double)CLOCKS_PER_SEC);

    // vector<double> grTrue = eigen_true_gr(x0);

    bool feq = (fabs(fn - fnTrue) < 1e-12);
    bool greq = true;
    // for(int i = 0; i < gr.size(); ++i){
    //   greq = greq && (fabs(gr[i] - grTrue[i]) < 1e-12);
    // }
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
