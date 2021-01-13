#include <initializer_list>
#include <iostream>
#include <memory>

using namespace std;

class AbstractPair {
  public:
    virtual void print(ostream& o) const = 0;
};

template <typename A, typename B>
class PairImpl : public AbstractPair{
  public:
    PairImpl(A& argA, B& argB) : a(argA), b(argB){
    }
    void print(ostream& o) const{
      o << a << " = " << b;
    }
  private:
    A a;
    B b;
};

class Pair {
public:
  template <typename A, typename B>
  Pair( A a, B b ) {
    //especialização do tipo de par
    p = make_shared<PairImpl<A, B>>(a ,b );
  }
  void print(ostream& o) const {
    p->print(o);
  }
  ~Pair(){
    cout << "destrutor de pair" << endl;
  }
private:
  shared_ptr<AbstractPair> p;
};

void print( ostream& o, initializer_list<Pair> lista ) {
  for( auto i = lista.begin(); i != lista.end(); i++){
    i->print(o);
    o << endl;
  }
  cout << "destrutor do par no initializer_list" << endl;
}

int main() {

  Pair p( "1", 2 );

  print(cout, {p});

  //print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  cout << "destrutor de p na main" << endl;
  return 0;  
}