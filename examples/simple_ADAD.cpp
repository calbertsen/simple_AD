

#include <GrAD/GrAD>
#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;

template<class T>
T simple_fn(T x, T y){
  return exp(-pow(x,T(2.0))/y) + y;
}

vector<double> simple_true_gr(double x, double y){
  vector<double> r(2);
  r[0] = -2.0 * x * exp(-pow(x,2.0)/y) / y;
  r[1] = pow(x,2.0) * exp(- pow(x,2.0)/y) / pow(y,2.0) + 1.0;
  return r;
}

void simple_ADAD_grad(int seed){

    using namespace GrAD;
  
    vector<double> res(8);
    clock_t t;
    double t1, t2, t3;

    srand(seed);

    ADparlist<double>* grd0 = new ADparlist<double>();
    ADparlist<AD<double> >* grd = new ADparlist<AD<double> >();

    vector<AD<double> > x0(2);
    x0[0] = AD<double>(rand() / (double)RAND_MAX);
    x0[1] = AD<double>(rand() / (double)RAND_MAX);

    grd0->Independent(x0);

    std::cout << std::endl << std::endl << "Running AD of AD example" << std::endl << std::endl;

    std::cout << "Function:\nf:=(x,y) -> exp(-x^2.0/y) + y;\n"; 
    
    std::cout << "values: \n";
    std::cout << x0[0].fn() << "  " << x0[1].fn() << "\n\n";

    std::cout << "\n\nCorresponding Maple code\n\n";
    std::cout << "f("<<x0[0].fn() <<","<< x0[1].fn() << ");\n";
    std::cout << "eval(diff(f(x, y), x), {x="<<x0[0].fn() <<",y="<< x0[1].fn() << "});\n";
    std::cout << "eval(diff(f(x, y), y), {x="<<x0[0].fn() <<",y="<< x0[1].fn() << "});\n";
    std::cout << "eval(diff(diff(f(x, y), x),x), {x="<<x0[0].fn() <<",y="<< x0[1].fn() << "});\n";
    std::cout << "eval(diff(diff(f(x, y), x),y), {x="<<x0[0].fn() <<",y="<< x0[1].fn() << "});\n";
    std::cout << "eval(diff(diff(f(x, y), y),x), {x="<<x0[0].fn() <<",y="<< x0[1].fn() << "});\n";
    std::cout << "eval(diff(diff(f(x, y), y),y), {x="<<x0[0].fn() <<",y="<< x0[1].fn() << "});\n";

    
    std::cout << "\n\nResults from C++\n\n";
    
    AD<AD<double> > x(x0[0]);
    AD<AD<double> > y(x0[1]);

    grd->Independent(x);
    grd->Independent(y);

    AD<AD<double> > z = simple_fn(x,y);
    AD<double> fn = z.fn();
    std::cout << "Function value:\n";
    std::cout << fn.fn() << "\n";

    std::cout << "\n\n";
    std::cout << "Gradient value:\n";
    vector<AD<double> > gr = z.gr();
    std::cout << gr[0].fn() << "  " << gr[1].fn() << "\n\n\n";

    std::cout << "Hessian value:\n";
    for(int i = 0; i < 2; ++i){
      vector<double> gri = gr[i].gr();
          for(int j = 0; j < 2; ++j)
    	    std::cout << gri[j] << "  ";
    	  std::cout << "\n";
    }

    std::cout << std::endl << std::endl;

    delete grd;
    return;
}



int main(){
  simple_ADAD_grad(123);
  return 0;
}
