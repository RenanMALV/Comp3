#include <iostream>
#include <algorithm>
#include <array>

#include "LS.cc"

using namespace std;

int main( int argc, char* argv[] ) {
  int tab[10] =  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  vector<int> v;
  
  tab |	 [ &v ]( int x ) { v.push_back( x ); };
  v | []( int x ) { return x % 2 == 0; } 
    | []( int x ) { return x*x / 10.0; } 
    | [] ( double x ) { cout << x << endl; };
   
  cout << endl;

  Intervalo( 9, 99 )  | []( auto x ) { cout << x << " "; };
  return 0;
}