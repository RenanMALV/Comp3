#include <iostream>
using namespace std;

class PilhaInt{
  #define MAX_PILHA 64
  public:
    PilhaInt(){
      topo = -1;
    }
    void empilha(int valor){
      pilha[++topo] = valor;
    }
    int desempilha(){
      return pilha[topo--];
    }
    void print(ostream& o){
      o << "[ ";
      for(int i = -1; i<topo;){
        i++;
        o << pilha[i];
        if(i == topo)
          o << " ]";
        else
          o << ", ";
      }
    }
    const PilhaInt& operator = (const PilhaInt& p){
      for(topo = -1; topo<p.topo;){
        topo++;
        pilha[topo] = p.pilha[topo]; 
      }
      return *this;
    }
    PilhaInt& operator << (int valor){
      empilha(valor);
      return *this;
    }
  private:
    int pilha[MAX_PILHA];
    int topo;
};

  int main(){
    PilhaInt q;
    q << 5;
    PilhaInt p;
    p << 25 << 1;
    q = p;
    q.print(cout);
    cout << endl;
    return 0;
  }