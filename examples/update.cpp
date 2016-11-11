

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

void update_grad(int seed){

    using namespace GrAD;
  
    vector<double> res(8);
    clock_t t;
    double t1, t2, t3;

    srand(seed);

    ADparlist<double>* grd = new ADparlist<double>();

    vector<double> x0(2);
    x0[0] = (rand() / (double)RAND_MAX);
    x0[1] = (rand() / (double)RAND_MAX);

    std::cout << std::endl << std::endl << "Running update example" << std::endl << std::endl;
    
    std::cout << "values: \n";
    std::cout << x0[0] << "  " << x0[1] << "\n\n";
    
    AD<double> x(x0[0]);
    AD<double> y(x0[1]);

    grd->Independent(x);
    grd->Independent(y);

    AD<double> z = simple_fn(x,y);
    double fn = z.fn();
    std::cout << "Function value:\n";
    std::cout << fn << "\n";

    std::cout << "\n\n";
    std::cout << "Gradient value:\n";
    vector<double> gr = z.gr();
    std::cout << gr[0] << "  " << gr[1] << "\n\n\n";

    x0[0] = (rand() / (double)RAND_MAX);
    x0[1] = (rand() / (double)RAND_MAX);
    z.update(x0);

    std::cout << "New values: \n";
    std::cout << x0[0] << "  " << x0[1] << "\n\n";
    std::cout << x.fn() << "  " << y.fn() << "\n\n";
    fn = z.fn();
    std::cout << "New Function value:\n";
    std::cout << fn << "\n";

    std::cout << "\n\n";
    std::cout << "New Gradient value:\n";
    gr = z.gr();
    std::cout << gr[0] << "  " << gr[1] << "\n\n\n";


    std::cout << std::endl << std::endl;
    
    return;
}



int main(){
  update_grad(123);
  return 0;
}
