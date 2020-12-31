#include <iostream>
#include <vector>

using namespace std;

class PilhaInt{
  public:
    //Construtor padrão
    PilhaInt(){
    }    
    //construtor fornecendo um tamanho específico
    PilhaInt(int tamanho){
      alocar(tamanho);
    }
    //construtor de cópia
    PilhaInt(PilhaInt& p){
      pilha = p.getPilha();
      //para vector não é necessário copiar membro a membro da pilha
      //for(auto i : p.getPilha()){
      //  empilha(i);
      //}
    }

    const vector<int>& getPilha() const{ return pilha; }

    int capacidade() const{
      return pilha.capacity();
    }

    void empilha(int valor){
      pilha.push_back(valor);
    }
    int desempilha(){
      auto elementoNoTopo = pilha.back();
      pilha.pop_back();
      return elementoNoTopo;
    }
    //exibe a pilha em uma stream de output
    void print(ostream& o){
      //pilha não vazia
      if(!pilha.empty()){
        o << "[ ";
        for(auto itr = pilha.cbegin(); itr != pilha.cend(); ++itr){
          o << *itr;
          if((itr+1) != pilha.cend())
            o << ", ";
        }
        o << " ]";
      }

    }
    //override do operador de atribuição
    const PilhaInt& operator = (const PilhaInt& p){
      if(this != &p){
        //para vector não é necessário copiar membro a membro da pilha
        pilha = p.getPilha();
        //for(auto pIterator : p.getPilha()){
        //  empilha(pIterator);  
        //}
      }
      return *this;
    }
    //override do operador de shift para empilhar
    PilhaInt& operator << (int valor){
      empilha(valor);
      return *this;
    }
  private:
    vector<int> pilha;

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
    */
    PilhaInt a{7};
    PilhaInt b{7};
    a << 8 << 3 << 1 << 4 << 5;
    a.print(cout); cout << endl;
    b << 0 << 0;
    a = b;
    a.print( cout ); cout << endl;
    b << 1000;
    a.print( cout ); cout << endl;
    return 0;
  }