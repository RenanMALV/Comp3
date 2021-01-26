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
    };
};

template< typename T>
class Object: public Undefined {
public:
  Object( T n ):t(n) {
    //implementar construtor do object
  }
private:
  T t;
};

class Int: public Undefined {
public:
  Int( int n ):n(n) {}
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
private:
  double n;
};

class String: public Undefined {
public:
  String( string n ):n(n) {
    cout << "criou a string no map " << endl;
  }
  virtual void print(ostream& o){
    o << n;
  }
private:
  string n;
};

class Var {
public:
  Var(): valor( new Undefined() ) {
    cout << "init a new Undefined var" << endl;
  }
  
  template< typename T>
  Var& operator = ( T obj ) {
    valor = shared_ptr<Undefined>( new Object( obj ) );
    return *this;
  }
  template<>
  Var& operator = ( int n ) {
    valor = shared_ptr<Undefined>( new Int( n ) );
    return *this;
  }
  template<>
  Var& operator = (const char* n ) {
    cout << "chamando construtor de char" << endl;
    valor = shared_ptr<Undefined>( new Char( n ) );
    return *this;
  }
  template<>
  Var& operator = ( double n ) {
    valor = shared_ptr<Undefined>( new Double( n ) );
    return *this;
  }
  template<>
  Var& operator = ( string n ) {
    cout << "chamando o construtor de String" << endl;
    valor = shared_ptr<Undefined>( new String( n ) );
    return *this;
  }
  

  //overload do [] para permitir localização no map
  Var& operator [] ( string key){
    if ( objs_map.find(key) == objs_map.end() ) {
      objs_map[key] = shared_ptr<Var>( new Var() );
      cout << "criou " << key << endl;
    }
    cout << "retornando um valor do map" << endl;
    return objs_map[key];
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