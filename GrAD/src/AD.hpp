// This file is part of GrAD, a C++ template library for
// graph based reverse mode automatic differentiation in C++
//
// Copyright (C), Christoffer Moesgaard Albertsen <cmoe@aqua.dtu.dk>

template<class T>
class AD {

public:
  
  ADnode<T>* root;

public:
  
  AD();
  AD(T x0, string name, ADparlist<T>* graph);
  AD(T x0);

  T forward_fn(vector<T> x);
  vector<T> forward_gr(vector<T> x);

  T fn();
  vector<T> gr();
  string JSON();
  void update(vector<T>& x);
  
  AD<T> operator+(const AD<T>& other) const;
  AD<T>& operator+=(const AD<T>& other);

  AD<T> operator-() const;
  AD<T> operator-(const AD<T>& other) const;
  AD<T>& operator-=(const AD<T>& other);

  AD<T> operator*(const AD<T>& other) const;
  AD<T>& operator*=(const AD<T>& other);

  AD<T> operator/(const AD<T>& other) const;
  AD<T>& operator/=(const AD<T>& other);

  // Friend declarations are not needed while root is public.
  // // Unary math
  // template<class U>
  // friend AD<U> sign(const AD<U>& x);
  // template<class U>
  // friend AD<U> abs(const AD<U>& x);
  // template<class U>
  // friend AD<U> fabs(const AD<U>& x);
  // template<class U>
  // friend AD<U> sqrt(const AD<U>& x);
  // template<class U>
  // friend AD<U> acos(const AD<U>& x);
  // template<class U>
  // friend AD<U> acosh(const AD<U>& x);
  // template<class U>
  // friend AD<U> asin(const AD<U>& x);
  // template<class U>
  // friend AD<U> asinh(const AD<U>& x);
  // template<class U>
  // friend AD<U> atan(const AD<U>& x);
  // template<class U>
  // friend AD<U> atanh(const AD<U>& x);
  // template<class U>
  // friend AD<U> cos(const AD<U>& x);
  // template<class U>
  // friend AD<U> cosh(const AD<U>& x);
  // template<class U>
  // friend AD<U> erf(const AD<U>& x);
  // template<class U>
  // friend AD<U> exp(const AD<U>& x);
  // template<class U>
  // friend AD<U> expm1(const AD<U>& x);
  // template<class U>
  // friend AD<U> log(const AD<U>& x);
  // template<class U>
  // friend AD<U> log1p(const AD<U>& x);
  // template<class U>
  // friend AD<U> log10(const AD<U>& x);
  // template<class U>
  // friend AD<U> sin(const AD<U>& x);
  // template<class U>
  // friend AD<U> sinh(const AD<U>& x);
  // template<class U>
  // friend AD<U> tan(const AD<U>& x);
  // template<class U>
  // friend AD<U> tanh(const AD<U>& x);

  // // Binary math
  // template<class U>
  // friend AD<U> atan2(const AD<U>& x,const AD<U>& y);
  // template<class U>
  // friend AD<U> pow(const AD<U>& x,const AD<U>& y);

};




template<class T>
AD<T>::AD(){
  root = NULL;
}

template<class T>
AD<T>::AD(T x0, string name, ADparlist<T>* graph){
  int i = graph->which(name);
  if(i < 0){
    root = new ADconstant<T>(x0);
  }else{
    root = new ADparameter<T>(x0,name,graph);
  }
}

template<class T>
AD<T>::AD(T x0){
  root = new ADconstant<T>(x0);
  this->root->setValue(x0);
}

template<class T>
T AD<T>::forward_fn(vector<T> x){
  return this->root->fn(x);
}

template<class T>
vector<T> AD<T>::forward_gr(vector<T> x){
  return this->root->dfn(x);
}

template<class T>
T AD<T>::fn(){
  return this->root->getValue();
}

template<class T>
vector<T> AD<T>::gr(){
  int np = this->root->grph->nparams;
  vector<T> x(np);
  for(int i = 0; i < np; ++i) x[i] = T(0.0);
  this->root->bdfn(1.0,x);
  return x;
}

template<class T>
string AD<T>::JSON(){
  return this->root->JSON();
}


template<class T>
AD<T> AD<T>::operator+(const AD<T>& other) const{
  AD<T> newAD = AD(*this);
  ADsum<T>* newRoot = new ADsum<T>(root,other.root);
  newAD.root = newRoot;
  return newAD;
}

template<class T>
AD<T>& AD<T>::operator+=(const AD<T>& other){
  //AD<T> newAD = AD(*this);
  ADsum<T>* newRoot = new ADsum<T>(root,other.root);
  root = newRoot;
  return *this;
}

template<class T>
AD<T> AD<T>::operator-() const{
  AD<T> newAD = AD(*this);
  ADusubtract<T>* newRoot = new ADusubtract<T>(root);
  newAD.root = newRoot;
  return newAD;
}

template<class T>
AD<T> AD<T>::operator-(const AD<T>& other) const{
  AD<T> newAD = AD(*this);
  ADsubtract<T>* newRoot = new ADsubtract<T>(root,other.root);
  newAD.root = newRoot;
  return newAD;
}

template<class T>
AD<T>& AD<T>::operator-=(const AD<T>& other){
  //AD<T> newAD = AD(*this);
  ADsubtract<T>* newRoot = new ADsubtract<T>(root,other.root);
  root = newRoot;
  return *this;
}

template<class T>
AD<T> AD<T>::operator*(const AD<T>& other) const{
  AD<T> newAD = AD(*this);
  ADprod<T>* newRoot = new ADprod<T>(root,other.root);
  newAD.root = newRoot;
  return newAD;
}

template<class T>
AD<T>& AD<T>::operator*=(const AD<T>& other){
  //AD<T> newAD = AD(*this);
  ADprod<T>* newRoot = new ADprod<T>(root,other.root);
  root = newRoot;
  return *this;
}


template<class T>
AD<T> AD<T>::operator/(const AD<T>& other) const{
  AD<T> newAD = AD(*this);
  ADdiv<T>* newRoot = new ADdiv<T>(root,other.root);
  newAD.root = newRoot;
  return newAD;
}

template<class T>
AD<T>& AD<T>::operator/=(const AD<T>& other){
  //AD<T> newAD = AD(*this);
  ADdiv<T>* newRoot = new ADdiv<T>(root,other.root);
  root = newRoot;
  return *this;
}

template<class T>
void AD<T>::update(vector<T>& x){
  root->update(x);
}
