#include <iostream>
using namespace std;

class PilhaInt{
  #define DEFAULT_SIZE 10
  public:
    //Construtor padrão
    PilhaInt(int tamanho = DEFAULT_SIZE) :topo(-1){
      alocar(tamanho);
    }
    //construtor de cópia
    PilhaInt(PilhaInt& p) :topo(-1){
      alocar(p.capacidade());
      for(topo = -1; topo<p.topo;){
        empilha(p.pilha[topo+1]);
      };
    }
    //destrutor
    ~PilhaInt(){
      free(pilha);
    }
    //redimensiona o tamanho da pilha
    void redimensiona(int n){
      pilha = (int *) realloc(pilha, n*sizeof(int));
      tamanho = n;
      if(topo >= n)
        topo = n-1;
    }
    int capacidade() const{
      return tamanho;
    }
    void empilha(int valor){
      if(topo==tamanho-1){
        redimensiona(tamanho*2);
      }
      pilha[++topo] = valor;
    }
    int desempilha(){
      return pilha[topo--];
    }
    //exibe a pilha em uma stream de output
    void print(ostream& o){
      //pilha não vazia
      if(topo != -1)
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
    //override do operador de atribuição
    const PilhaInt& operator = (const PilhaInt& p){
      if(this != &p){
        free(pilha);
        alocar(p.capacidade());
        for(topo = -1; topo<p.topo;){
          empilha(p.pilha[topo+1]);  
        }
      }
      return *this;
    }
    //override do operador de shift para empilhar
    PilhaInt& operator << (int valor){
      empilha(valor);
      return *this;
    }
  private:
    int *pilha;
    int topo;
    int tamanho;

    //alocação dinâmica da pilha
    void alocar(int tamanho){
      pilha = (int *) malloc(tamanho*sizeof(int));
      this->tamanho = tamanho;
    }
};

  int main(){
    /*PilhaInt q(2);
    q << 5 << 6;
    q.print(cout);
    q.redimensiona(1);
    q.print(cout);


    PilhaInt p(q);
    p.desempilha();
    p.print(cout);

    cout << endl << q.capacidade() << "  -  " << p.capacidade() << endl;
    p << 25 << 26 << 27;
    q.print(cout);
    p.print(cout);
    cout << endl << q.capacidade() << "  -  " << p.capacidade() << endl;

    q = q;
    
    PilhaInt a{7};
    PilhaInt b{7};
    a << 8 << 3 << 1 << 4 << 5;
    b << 0 << 0;
    a = b;
    a.print( cout ); cout << endl;
    */
    return 0;
  }