#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <type_traits>
#include <functional>

#include "var.cc"

using namespace std;
/*
Var print( const Var& o ) {
  cout << "{ nome: " << o["nome"]
       << ", idade: " << o["idade"]( o )
       << ", nascimento: " << o["nascimento"]
       << ", print: " << o["print"] 
       << ", atr: " << o["atr"] 
       << " }" << endl;
       
  return Var();     
}
*/
void imprime( Var v ) {
    v["print"]( v );
}

int main( int argc, char* argv[] ) try {     
  
/* TESTCASE-PLACE-HOLDER */
  Var a, b = 10;
  cout << a <<b << endl;
  b = "eu b mudei de tipo";
  cout << a << b << endl;
  string s = "teste";
  /*a = "teste";
  cout << a << endl;
  a = 2;
  cout << a << endl;
  b["atr"] = "string on var";
  cout << b["atr"] << endl;
  b["atr"] = [](){cout << endl;};
  cout << b["atr"] << endl;
  Var arr[2];
  arr[0] = "indice 0";
  arr[1] = "indice 1";
  cout << arr[0] << arr[1] << endl;*/
  return 0;
} catch( Var::Erro e ) {
  cout << "Erro fatal: " << e() << endl;
}