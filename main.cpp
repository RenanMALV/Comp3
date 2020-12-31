#include <initializer_list>
#include <iostream>

using namespace std;

class AbstractPair {
  public:
    virtual void print(ostream& o) = 0;
};

template <typename A, typename B>
class PairImpl : public AbstractPair{
  public:
    PairImpl(A argA, B argB) : a(argA), b(argB){
    }
    void print(ostream& o){
      //cout << endl << "[debug] called generic print inside a pair implementation" << endl;
      o << a << " = " << b;
    }
  private:
    A a;
    B b;
};

template <>
class PairImpl <const char*, int> : public AbstractPair{
  public:
    PairImpl(const char* argA, int argB) : a(argA), b(argB){
       //cout << endl << "[debug] called pair implementation assign constructor" << endl;
    }
    void print(ostream& o){
       //cout << endl << "[debug] called print inside a pair implementation and send result to output stream" << endl;
      o << a << " = " << b;
    }
  private:
    const char* a;
    int b;
};

template <>
class PairImpl<int, const char*> : public AbstractPair{
  public:
    PairImpl(int argA, const char* argB) : a(argA), b(argB){}
    void print(ostream& o){
      o << a << " = " << b;
    }
  private:
    int a;
    const char* b;
};

class Pair {
public:
  template <typename A, typename B>
  Pair( A a, B b ) {
    //especialização do tipo de par
    p = new PairImpl<A, B>(a ,b );
  }
  void print(ostream& o){
    //cout << endl << "[debug] called print inside a pair" << endl;
    p->print(o);
  }
private:
  AbstractPair *p = nullptr;
};

void print( ostream& o, initializer_list<Pair> lista ) {
  //cout << endl << "[debug] static print called" << endl;
  for( Pair par : lista){
    //cout << endl << "[debug] Encountered a Pair in initializer list" << endl;
    par.print(o);
    o << endl;
  }
}

int main() {

  Pair p( "1", 2 );

  //print(cout, {p});

  print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  return 0;  
}