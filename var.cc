#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <memory>
#include <map>

using namespace std;



class Undefined{
  public:
    virtual void print(ostream& o){
      o << "Undefined";
    }
    
};

template< typename T>
class Object: public Undefined {
public:
  Object( T n ):t(n) {
    //implementar construtor do object
  }
  virtual void print(ostream& o){
    o << t;
  }
  T get_obj(){
    return t;
  }
private:
  T t;
};

class Int: public Undefined {
public:
  Int( int n ):n(n) {}
  virtual void print(ostream& o){
    o << n;
  }
private:
  int n;
};

class Char: public Undefined {
public:
  Char(const char* n ):n(n) {}
  virtual void print(ostream& o){
    o << n;
  }
private:
  const char* n;
};

class Double: public Undefined {
public:
  Double( double n ):n(n) {}
  virtual void print(ostream& o){
    o << n;
  }
private:
  double n;
};

class String: public Undefined {
public:
  String( string n ):n(n) {
  }
  virtual void print(ostream& o){
    o << n;
  }
private:
  string n;
};

class Var {
public:
  //construtor sem parametros inicia em Undefined
  Var(): valor( new Undefined() ) {
  }
  //construtor com parametros chama os operadores de atribuicao da classe passando o paramentro recebido
  template< typename N>
  Var(N arg){
    *this = arg;
  }
  //operador de chamada de função
  template<typename Func_call_T>
  auto operator ()(Func_call_T param){
    return (invoke(valor->get_obj()))(param);
  }

  template< typename T>
  Var& operator = (T obj ) {
    valor = shared_ptr<Object<T>>( new Object( obj ) );
    return *this;
  }
  
  Var& operator = ( int n ) {
    valor = shared_ptr<Int>( new Int( n ) );
    return *this;
  }
  Var& operator = (const char* n ) {
    valor = shared_ptr<Char>( new Char( n ) );
    return *this;
  }
  Var& operator = ( double n ) {
    valor = shared_ptr<Double>( new Double( n ) );
    return *this;
  }
  Var& operator = ( string n ) {
    valor = shared_ptr<String>( new String( n ) );
    return *this;
  }
  

  //overload do [] para permitir localização no map
  Var& operator [] ( string key){
    if ( objs_map.find(key) == objs_map.end() ) {
      objs_map[key] = shared_ptr<Var>( new Var() );
    }
    return objs_map[key];
  }

  //tratando como array de var
  Var& operator [] ( int key){
    if(!arr_counter)
    for ( ; arr_counter<key; ++arr_counter ) {
      objs_arr[arr_counter] = shared_ptr<Var>( new Var() );
      return *this;
    }
    return objs_arr[key];
  }

  void print(ostream& o){
    valor->print(o);
  }

// Use essa classe para sinalizar exceções.
class Erro {
public:
  Erro( string msg ): msg(msg) {}
  
  string operator()() const {
    return msg;
  }
  
private:
  string msg;
};
//fim da classe erro
  
private:
  map<string,Var> objs_map;
  map<int,Var> objs_arr;
  int arr_counter = 0;
  shared_ptr<Undefined> valor;
};

ostream& operator << (ostream& o, Var&& v) {
	v.print(o);
  return o;
}

ostream& operator << (ostream& o, Var& v) {
	v.print(o);
  return o;
}
// Int, Char, Double, Object, Function, Array