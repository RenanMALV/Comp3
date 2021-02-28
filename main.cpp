#include <iostream>
#include <algorithm>
#include <array>

#include "otimizador.cc"

using namespace std;



int main() {
  Matriz<100,1> a;
  Matriz<1,100> b;
  Matriz<100,100> c;

  auto f = Apply( []( double x ){ return rand(); } );
  b = f(b);
  a = f(a);

  Matriz<100,100> x1 = a * b;
  Matriz<100,100> x2 = x1 * c;

  Matriz<100,100> y = a * b * c;
  
  // aplicar uma função à uma matriz:
  /* Vai calcular c[i][j] = g( c[i][j] ); */
  //auto d = f(a) * b;
  
  //for( int i = 0; i < d.nLin(); i++ )
  //  for( int j = 0; j < d.nCol(); j++ )
  //    cout << d[i][j] << endl;
  
  return 0;
}