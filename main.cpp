#include <iostream>
#include <algorithm>
#include <array>

#include "deriv.cc"

using namespace std;

int main() {
  X x;
  auto f = log( (8.1/(x+1.0)->*3 - 9.2 ) * (x + 3.0) *sin( cos( x / 3.14 ) ) + x );
  double v = 10;
  
  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;

  cout << "f(x)=" << f.str() << ", f'(x)=" << f.dx_str() << endl;
}