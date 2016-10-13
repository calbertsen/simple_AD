// This file is part of GrAD, a C++ template library for
// graph based reverse mode automatic differentiation in C++
//
// Copyright (C), Christoffer Moesgaard Albertsen <cmoe@aqua.dtu.dk>


template<class T>
struct ADparlist {
  
  int nparams;
  vector<string> params;

  ADparlist();

  ADparlist(vector<string> par);
    
  int which(string n0);

};



template<class T>
ADparlist<T>::ADparlist(){
  params = vector<string>();
  nparams = 0;
}


template<class T>
ADparlist<T>::ADparlist(vector<string> par){
  params = par;
  nparams = par.size();
}

template<class T>
int ADparlist<T>::which(string n0){
  int res = -1;
  if(nparams == 0)
    return res;
  int i = 0;
  do {
    if(n0.compare(params[i]) == 0)
      res = i;
    ++i;
  } while(res < 0 && i < nparams);
  return res;
}

// void ADparlist::addParam(string par){
//   int i = which(par);
//   if(i == -1){
//     params.push_back(par);
//     nparams++;
//   }
// }


