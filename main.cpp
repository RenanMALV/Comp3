#include <vector>
#include <iostream>

using namespace std;

template<typename T, typename F>
T* operator | (T& t, F func ) {
  for(auto x : t){
    func(x);
  }
  return &t;
}
template<typename ArrT, int n,typename F>
ArrT* operator | (ArrT (&arr)[n], F func ) {
  for(int i=0; i<n; ++i){
    func(arr[i]);
  }
  return arr;
}

void print( int x ) { cout << x << " "; }

int main( int argc, char* argv[]) {     

  double tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
  vector<int> v{ 2 , 6, 8 };
  tab | []( double x ) { cout << x*x << endl; };
  tab | [ &v ]( int x ) { v.push_back( x ); };
  v | []( int x ) { cout << x*x << endl; };
  v | &print;
}