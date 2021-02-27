#include <iostream>
#include <algorithm>
#include <array>

#include "otimizador.cc"

using namespace std;



int main() {
  Matriz<10,20> a;
  Matriz<20,3> b;
  cout << b[0][0] << endl;
  b[0][0] = 10;
  cout << b[0][0] << endl;

  //auto c = a*b;
  
  // aplicar uma função à uma matriz:
  
  auto f = Apply( []( double x ){ return rand(); } );
  b = f(b);
  //c = f(c);
  /* Vai calcular c[i][j] = g( c[i][j] ); */
  //auto d = f(a) * b;
  
  //for( int i = 0; i < d.nLin(); i++ )
  //  for( int j = 0; j < d.nCol(); j++ )
  //    cout << d[i][j] << endl;
  
  return 0;
}