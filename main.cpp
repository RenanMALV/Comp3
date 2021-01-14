#include <vector>
#include <iostream>

using namespace std;

void print( int x ) { cout << x << " "; }
template<typename F>
bool filter( const int& x, F func) { return func(x); }

template<typename T, typename F>
T operator | (T t, F func ) {
  cout << typeid(decltype(func(0))).name();
  if(typeid(bool) == typeid(decltype(func(0)))){
    cout << " funcão bool" << endl;
    for(auto x : t){
      filter(x, func);
    }
  }
  else
    for(auto x : t){
      func(x);
    }
  return t;
}
template<typename ArrT, int n,typename F>
ArrT* operator | (ArrT (&arr)[n],const F& func ) {
  for(int i=0; i<n; ++i){
    func(arr[i]);
  }
  return arr;
}

int main( int argc, char* argv[]) {     

  //double tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
  vector<int> v{ 2 , 7, 8 };
  //tab | []( double x ) { cout << x*x << endl; };
  //tab | [ &v ]( int x ) { v.push_back( x ); };
  //v | []( int x ) { cout << x*x << endl; };
  //v | []( int x ) { return x % 2 == 0; }; 
  v | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << endl; };
}