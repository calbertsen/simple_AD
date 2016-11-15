// This file is part of GrAD, a C++ template library for
// graph based reverse mode automatic differentiation in C++
//
// Copyright (C), Christoffer Moesgaard Albertsen <cmoe@aqua.dtu.dk>



template<class T>
struct ADnode {

  ADparlist<T>* grph;

  vector<ADnode<T>* > parents;
  vector<const AD<T>* > owners;

  bool isBaseParam;
  string baseName;
  int whichParam;
  ADnode<T>* ptrL;
  ADnode<T>* ptrR;
  T curval;

  virtual T fn(vector<T> x);
  virtual vector<T> dfn(vector<T> x);

  virtual void bdfn(T w, vector<T>& theta);
  virtual void update(vector<T>& theta);

  virtual string JSON();
  
  void setValue(T x0);
  T getValue();

  void addParent(ADnode<T>* p);
  void removeParent(ADnode<T>* p);
  void prune(AD<T>* requester);
  int whichParent(ADnode<T>* p);

  void addOwner(const AD<T>* o);
  void removeOwner(const AD<T>* o);
  int whichOwner(const AD<T>* o);
  
  
protected:
  ADnode();
  ADnode(string name, int paramNum, ADparlist<T>* graph);
  ADnode(string name);
  ADnode(string name, ADnode<T>* L, ADnode<T>* R);
  ADnode(string name, ADnode<T>* L);
  ADnode(string name, ADnode<T>& L, ADnode<T>& R);
};



template<class T>
ADnode<T>::ADnode() : isBaseParam(false), baseName("UNINITIALIZED"), parents()
{
  grph = NULL;
  whichParam = -100;
  ptrL = NULL;
  ptrR = NULL;
}

template<class T>
ADnode<T>::ADnode(string name, int paramNum,ADparlist<T>* graph) : isBaseParam(true), baseName(name), whichParam(paramNum), parents()
{ 
  grph = graph;
  if(whichParam == -1)
    throw 101;
  ptrL = NULL;
  ptrR = NULL;
};

template<class T>
ADnode<T>::ADnode(string name) : isBaseParam(false), baseName(name), parents()
{ 
  grph = NULL;
  whichParam = -1;
  ptrL = NULL;
  ptrR = NULL;
};


template<class T>
ADnode<T>::ADnode(string name, ADnode<T>* L, ADnode<T>* R) : isBaseParam(false), baseName(name), parents() {
  L->addParent(this);
  R->addParent(this);
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
ADnode<T>::ADnode(string name, ADnode<T>* L) : isBaseParam(false), baseName(name), parents() {
  L->addParent(this);
  grph = L->grph;
  ptrL = L;
  ptrR = NULL;
  whichParam = -100;
}

template<class T>
ADnode<T>::ADnode(string name, ADnode<T>& L, ADnode<T>& R) : isBaseParam(false), baseName(name), parents(){
  L.addParent(this);
  R.addParent(this);
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

template<class T>
int ADnode<T>::whichParent(ADnode<T>* p){
  int res = -1;
  int i = 0;
  if(parents.size() == 0)
    return res;
  
  do {
    if(p == parents[i])
      res = i;
    ++i;
  } while(res < 0 && i < parents.size());
  return res;
}


template<class T>
void ADnode<T>::addParent(ADnode<T>* p){
  int wp = whichParent(p);
  if(wp < 0)
    parents.push_back(p);
  return;
};

template<class T>
void ADnode<T>::removeParent(ADnode<T>* p){
  int wp = whichParent(p);
  if(wp > -1)
    parents.erase(parents.begin() + wp);
  return;
};




template<class T>
int ADnode<T>::whichOwner(const AD<T>* o){
  int res = -1;
  int i = 0;
  if(owners.size() == 0)
    return res;
  
  do {
    if(o == owners[i])
      res = i;
    ++i;
  } while(res < 0 && i < owners.size());
  return res;
}


template<class T>
void ADnode<T>::addOwner(const AD<T>* o){
  int wo = whichOwner(o);
  if(wo < 0)
    owners.push_back(o);
  return;
};

template<class T>
void ADnode<T>::removeOwner(const AD<T>* o){
  int wo = whichOwner(o);
  if(wo > -1)
    owners.erase(owners.begin() + wo);
  return;
};


template<class T>
void ADnode<T>::prune(AD<T>* requester){
  removeOwner(requester);
  if(parents.size() == 0 && owners.size() == 0){
    if(ptrL != NULL){
      ptrL->removeParent(this);
      ptrL->prune(NULL);
      ptrL = NULL;
    }
    if(ptrR != NULL){
      ptrR->removeParent(this);
      ptrR->prune(NULL);
      ptrR = NULL;
    }
    if(requester != NULL || !isBaseParam)// && !isBaseParam)
      delete this;
  }
};
