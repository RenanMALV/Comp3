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

//Função apply genérica
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

//Função apply recebendo um initializer_list
//coleção de elementos t
//função f que será aplicada aos elementos
//retorno do tipo de f(t[0])
template <typename K, typename F>
auto apply(initializer_list<K> t,F f) -> vector<decltype(f(t.begin()[0]))> {
  vector<decltype(f(t.begin()[0]))> ret;
  for(auto element : t){
    ret.push_back(f(element));
  }
  return ret;  
}

//Função apply recebendo um array de int
//coleção de elementos t
//número n de elementos no array
//função f que será aplicada aos elementos
//retorno do tipo de f(t[0])
template <typename F, int n>
auto apply(int(& t)[n],F f) -> vector<decltype(f(t[0]))> {
  vector<decltype(f(t[0]))> ret;
  for(int i = 0; i<n; ++i){
    ret.push_back(f(t[i]));
  }
  return ret;  
}

int main( int argc, char* argv[]) {     

/* TESTCASE-PLACE-HOLDER */
  //auto v = ;
  //cout << typeid(v).name();
  //auto s = apply( v, roman);
cout << ::apply( { 1, 3, 5 }, FunctorSimples() );

//int v[] = { 1, 2, 3, 4, 5 };
//vector<int> r = ::apply( v, id );
//cout << r;
return 0;
}