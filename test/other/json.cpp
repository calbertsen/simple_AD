
#include <GrAD/GrAD>
#include <cstdlib>
#include <iostream>

using std::vector;

vector<bool> json_test(int seed){

  using namespace GrAD;

  vector<bool> rOut(2);
  
  
  srand(seed);
  // Must be between -Inf and Inf
  double x0 = rand()/(double)RAND_MAX;
  double y0 = rand()/(double)RAND_MAX;
  double z0 = rand()/(double)RAND_MAX;

  
  vector<string> params(2);
  params[0] = "x";
  params[1] = "y";
  ADparlist<double>* grd = new ADparlist<double>(params);

  AD<double> x(x0,"x",grd);
  AD<double> y(y0,"y",grd);
  AD<double> z(z0,"z",grd);

  AD<double> res = exp(-pow(x,2.0)/y) + y/z;
  double fn = res.fn();
  vector<double> gr = res.gr();

  std::cout << "\n\nTesting JSON\n\n";

  std::cout << "Function value: " << fn << std::endl;
  std::cout << "gradient value: ";
  for(int i = 0; i < gr.size(); ++i)
    std::cout << "  " << gr[i];
  std::cout << std::endl;

  
  string s0 = res.JSON();
  std::cout << s0 << std::endl<<std::endl;
  
  return rOut;

}


int main(){
  vector<bool> r = json_test(289734);
  return 0;
}


