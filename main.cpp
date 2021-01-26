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

void imprime( Var v ) {
    v["print"]( v );
}
*/
int main( int argc, char* argv[] ) try {     
  
/* TESTCASE-PLACE-HOLDER */
  Var a;
  Var b;
  string s = "teste";
  a = "teste";
  cout << a << endl;
  a = 2;
  cout << a << endl;
  b["atr"] = "string on var";
  cout << b["atr"] << endl;
  b["atr"] = 2;
  cout << b["atr"] << endl;
  return 0;
} catch( Var::Erro e ) {
  cout << "Erro fatal: " << e() << endl;
}