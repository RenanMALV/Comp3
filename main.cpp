#include <iostream>
#include <algorithm>
#include <array>

#include "deriv.cc"

using namespace std;

int main() {
  X x;
  auto f = exp( x * log( x - 8.0 ) + 1.0 );
  double v = 10;
  
  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;

  cout << "f(x)=" << f.str() << ", f'(x)=" << f.dx_str() << endl;
}