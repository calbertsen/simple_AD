

template<class T>
T eigen_fn(Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> x){
  Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> xt = x.transpose();
  Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> A = x * xt;
  return A.trace();
}

