// This file is part of GrAD, a C++ template library for
// graph based reverse mode automatic differentiation in C++
//
// Copyright (C), Christoffer Moesgaard Albertsen <cmoe@aqua.dtu.dk>


template<class T>
struct ADsin : public ADnode<T>{


  ADsin(ADnode<T>* L);
  ADsin(ADnode<T> L);

  T fn(vector<T> x);
  vector<T> dfn(vector<T> x);
  void bdfn(T w, vector<T>& theta);
  void update(vector<T>& theta);

};

template<class T>
ADsin<T>::ADsin(ADnode<T>* L): ADnode<T>("ADSIN",L){
  T cv = sin(this->ptrL->curval);
  this->setValue(cv);
}
template<class T>
ADsin<T>::ADsin(ADnode<T> L): ADnode<T>("ADSIN",&L){
  T cv = sin(this->ptrL->curval);
  this->setValue(cv);
}

template<class T>
T ADsin<T>::fn(vector<T> x){
  return sin(this->ptrL->fn(x));
}

template<class T>
vector<T> ADsin<T>::dfn(vector<T> x){
  vector<T> res(x.size());
  vector<T> dfnL = this->ptrL->dfn(x);
  T fnL = this->ptrL->fn(x);
  for(int i = 0; (size_t)i < x.size(); ++i){
    res[i] = dfnL[i] * cos(fnL);
  }
  return res;      
}


template<class T>
AD<T> sin(const AD<T>& x){
  AD<T> newAD;
  ADnode<T>* orx = x.getRoot();
  newAD.setRoot(new ADsin<T>(orx));
  return newAD;
}


template<class T>
void ADsin<T>::bdfn(T w, vector<T>& theta){
  T fnL = this->ptrL->getValue();
  T wL = w * cos(fnL);
  this->ptrL->bdfn(wL,theta);
  return;
}

template<class T>
void ADsin<T>::update(vector<T>& theta){
  this->ptrL->update(theta);
  T cv = sin(this->ptrL->curval);
  this->setValue(cv);
  return;
}

