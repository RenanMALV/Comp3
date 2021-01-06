#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>
//#include "apply.cc"

using namespace std;

double seno( double n ) { return sin(n); }
int id( int n ) { return n; }
string roman( int n ) {
    map<int,string> rom = { { 1, "I" }, { 2, "II" }, { 3, "III" }, { 4, "IV" }, { 5, "V" }, { 6, "VI" }, { 7, "VII" }, { 8, "VIII" } } ; 

    return rom[n]; 
}

struct FunctorSimples { 
    string operator()( int n ) { return roman( n ) + "!"; }
};

struct FunctorTemplate { 
    template <typename T>
    T operator()( T n ) { return n+n; }
};

template <typename T>
ostream& operator << ( ostream& o, const vector<T>& v ) {
    o << "[ ";
    for( auto x : v )
        o << x << " ";
        
    return o << "]";
}

//Função apply
//coleção de elementos t
//função f que será aplicada aos elementos
//retorno do tipo f(t[n])
template <typename T,typename F>
auto apply(T t,F f) -> vector<decltype(f(t.begin()[0]))> {
  vector<decltype(f(t.begin()[0]))> ret;
  for(auto element : t){
    ret.push_back(f(element));
  }
  return ret;  
}

int main( int argc, char* argv[]) {     

/* TESTCASE-PLACE-HOLDER */
  //auto v = ;
  //cout << typeid(v).name();
  //auto s = apply( v, roman);

//cout << apply( { 1, 3, 5 }, FunctorSimples() );
return 0;
}