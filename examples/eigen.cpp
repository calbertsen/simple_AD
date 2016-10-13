
#include <Eigen/Dense>
#include <GrAD/GrAD>
#include <iostream>
#include <vector>
using std::vector;

#ifdef __cplusplus
#if __cplusplus >= 201103L


void eigen_grad(int seed){

    using namespace GrAD;
    using namespace Eigen;

    std::cout << std::endl << std::endl << "Running Eigen example" << std::endl << std::endl;
      
    typedef Eigen::Matrix<AD<double>,Dynamic,1> ADVec;
  
    vector<string> params = {"v1","v2","v3","w1","w2","w3"};
    ADparlist<double>* grd = new ADparlist<double>(params);

    ADVec v(3);
    ADVec w(3);
    v[0] = AD<double>(1,"v1",grd);
    v[1] = AD<double>(2,"v2",grd);
    v[2] = AD<double>(3,"v3",grd);
    w[0] = AD<double>(0,"w1",grd);
    w[1] = AD<double>(1,"w2",grd);
    w[2] = AD<double>(2,"w3",grd);

    Matrix<AD<double>,Dynamic,Dynamic> z = v.transpose() * w;
    std::cout << "Dimension of inner product:" << std::endl;
    std::cout << z.rows() << " x " << z.cols() << std::endl<< std::endl<< std::endl;
    std::cout << "Function value:" << std::endl;
    std::cout << z(0,0).fn() << std::endl<< std::endl<< std::endl;
    vector<double> gr = z(0,0).gr();
    std::cout << "Gradient value:" << std::endl;
    for(int i = 0; i < gr.size(); ++i)
      std::cout << gr[i] << "  ";

    std::cout << std::endl << std::endl;
   
    return;
}



int main(){
  eigen_grad(123);
  return 0;
}


#else
int main(){
  std::cout << std::endl << std::endl << "Eigen example skipped for C++ versions before 11" << std::endl << std::endl;
  return 0;
}
#endif
#endif
