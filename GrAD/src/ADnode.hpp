// This file is part of GrAD, a C++ template library for
// graph based reverse mode automatic differentiation in C++
//
// Copyright (C), Christoffer Moesgaard Albertsen <cmoe@aqua.dtu.dk>



template<class T>
struct ADnode {

  ADparlist<T>* grph;

  bool isBaseParam;
  string baseName;
  int whichParam;
  ADnode<T>* ptrL;
  ADnode<T>* ptrR;
  T curval;

  // virtual T fn(vector<T> x){
  //   std::cout << "not the fn i wanted\n";
  //   return 0.0;
  // };
  // virtual vector<T> dfn(vector<T> x){
  //   std::cout << "not the dfn i wanted\n";
  //   vector<T> res(grph->nparams);
  //   return res;
  // };

  virtual T fn(vector<T> x);
  virtual vector<T> dfn(vector<T> x);

  virtual void bdfn(T w, vector<T>& theta);
  virtual void update(vector<T>& theta);

  virtual string JSON();

  void setValue(T x0);
  T getValue();
  
protected:
  ADnode();
  ADnode(string name, int paramNum, ADparlist<T>* graph);
  ADnode(string name);
  ADnode(string name, ADnode<T>* L, ADnode<T>* R);
  ADnode(string name, ADnode<T>* L);
  ADnode(string name, ADnode<T> L, ADnode<T> R);
  
};



template<class T>
ADnode<T>::ADnode() : isBaseParam(false), baseName("UNINITIALIZED")
{
  grph = NULL;
  whichParam = -100;
  ptrL = NULL;
  ptrR = NULL;
}

template<class T>
ADnode<T>::ADnode(string name, int paramNum,ADparlist<T>* graph) : isBaseParam(true), baseName(name), whichParam(paramNum)
{ // Construct from "nothing"; creates a base parameter
  grph = graph;
  //grph->addParam(name);
  //whichParam = graph->which(name);
  if(whichParam == -1)
    throw 101;//std::invalid_argument("Parameter must be pre-registered in graph");
  ptrL = NULL;
  ptrR = NULL;
};

template<class T>
ADnode<T>::ADnode(string name) : isBaseParam(false), baseName(name)
{ // Construct from "nothing"; creates a constant
  grph = NULL;
  //grph->addParam(name);
  whichParam = -1;
  ptrL = NULL;
  ptrR = NULL;
};


template<class T>
ADnode<T>::ADnode(string name, ADnode<T>* L, ADnode<T>* R) : isBaseParam(false), baseName(name){
  if((L->grph != R->grph) && L->grph != NULL && R->grph != NULL)
    throw 99; // Graphs must match

  if(L->grph != NULL){
    grph = L->grph;
  }else if(R->grph != NULL){
    grph = R->grph;
  }else{
    grph = NULL;
  }
  ptrL = L;
  ptrR = R;
  whichParam = -100;
}

template<class T>
ADnode<T>::ADnode(string name, ADnode<T>* L) : isBaseParam(false), baseName(name){
  grph = L->grph;
  ptrL = L;
  ptrR = NULL;
  whichParam = -100;
}

template<class T>
ADnode<T>::ADnode(string name, ADnode<T> L, ADnode<T> R) : isBaseParam(false), baseName(name){
  if(L.grph != R.grph)
    throw 99; // Graphs must match

  if(L.grph != NULL){
    grph = L.grph;
  }else if(R.grph != NULL){
    grph = R.grph;
  }else{
    grph = NULL;
  }
  ptrL = &L;
  ptrR = &R;
  whichParam = -100;
}


template<class T>
T ADnode<T>::fn(vector<T> x){
  throw 100;
};

template<class T>
vector<T> ADnode<T>::dfn(vector<T> x){
  throw 100;
};

template<class T>
void ADnode<T>::bdfn(T w, vector<T>& theta){
  throw 100;
};


template<class T>
string ADnode<T>::JSON(){
  if(ptrL != NULL && ptrR != NULL){
    string sl = ptrL->JSON();
    string sr = ptrR->JSON();
    return "{\"name\":\""+baseName+"\", \"left\":"+sl+", \"right\":"+sr+"}";
  }else if(ptrL != NULL && ptrR == NULL){
    string sl = ptrL->JSON();
    return "{\"name\":\""+baseName+"\", \"left\":"+sl+", \"right\":null}";
  }else if(ptrL == NULL && ptrR != NULL){
    string sr = ptrR->JSON();
    return "{\"name\":\""+baseName+"\", \"left\":null, \"right\":"+sr+"}";
  }else{
    return "{\"name\":\""+baseName+"\", \"left\":null, \"right\":null}";
  }

}

template<class T>
void ADnode<T>::update(vector<T>& theta){
  throw 999;
}


template<class T>
void ADnode<T>::setValue(T x0){
  curval = x0;
};

template<class T>
T ADnode<T>::getValue(){
  return curval;
};
