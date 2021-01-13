#include <vector>
#include <iostream>

using namespace std;


template<typename T>
vector<T>& operator | (vector<T>& t, bool (*func)(int) ) {
  vector<T> aux;
  for(auto x : t){
    if(func(x))
      aux.push_back(x);
  }
  t = aux;
  return t;
}
template<typename T>
vector<T>& operator | (vector<T>& t, void (*func)( int ) ) {
  for(auto x : t){
    func(x);
  }
  return t;
}
template<typename T>
vector<T>& operator | (vector<T>& t, void (*func)(double) ) {
  for(auto x : t){
    func(x);
  }
  return t;
}
template<typename T>
vector<T>& operator | (vector<T>& t, void (*func)(string) ) {
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

void print( int x ) { cout << x << " "; }

int main( int argc, char* argv[]) {     

  double tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
  vector<int> v{ 2 , 7, 8 };
  tab | []( double x ) { cout << x*x << endl; };
  tab | [ &v ]( int x ) { v.push_back( x ); };
  v | []( int x ) { cout << x*x << endl; };
  v | []( int x ) { return x % 2 == 0; };
  v | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << endl; };
}