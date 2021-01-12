#include <iostream>

using namespace std;

//implementação do vetor geométrico
template<int N, typename T>
class VetorImpl{
  public:
    void push(T val){
      if(contAtrib<N){
        componentes[contAtrib] = val;
        ++contAtrib;
      }
      else{
        contAtrib=0;
        componentes[contAtrib++] = val;
      }
    }
    T* print_componentes(){
      return componentes;
    }
  private:
    T componentes[N] = {};
    //conta quantas componentes foram atribuidas
    int contAtrib = 0;
};

//classe que lida com a interface entre implementações de vetores
template<int N, typename T>
class Vetor{
  public:
    //classe auxiliar para postergar a operação de atribuição
    class Atr_opp {
      private:
        Vetor *_vetor;
	      Atr_opp( Vetor* v ): _vetor( v ) {}
        friend class Vetor;
      public:
	      Atr_opp operator , ( T n ) {
          //chama novamente o operador "=" de Vetor
	        *_vetor = n;
	        return *this;
	      }
	    
    };
    //opperator "=" overload
    Atr_opp operator = ( T n ) {
      _vetorGeometrico.push( n );
      //chama a classe que lida com as atribuições múltiplas
      return Atr_opp( this );
    }

    //recebe as componentes de um vetor implementado e redireciona para a chamada de função
    T* printable_componentes(){
      return _vetorGeometrico.print_componentes();
    }

    //Adição de vetores, retorna um vetor.
    template<typename Tv>
    auto operator + (Vetor<N,Tv> v)  -> Vetor<N, decltype(this->printable_componentes()[0] + v.printable_componentes()[0])>{
      Vetor<N, decltype(this->printable_componentes()[0] + v.printable_componentes()[0])> resultante;
      for(int i=0; i<N; ++i)
	      resultante = printable_componentes()[i] + v.printable_componentes()[i];
      return resultante;
    }
    

    //Subtração de vetores, retorna um vetor.
    template<typename Tv>
    auto operator - (Vetor<N,Tv> v)  -> Vetor<N, decltype(this->printable_componentes()[0] - v.printable_componentes()[0])>{
      Vetor<N, decltype(this->printable_componentes()[0] - v.printable_componentes()[0])> resultante;
      for(int i=0; i<N; ++i)
	      resultante = printable_componentes()[i] - v.printable_componentes()[i];
      return resultante;
    }
    
  private:
    VetorImpl<N, T> _vetorGeometrico;
};

//Multiplicação por um escalar, retorna um vetor.
template<int N, typename Ts, typename Tv>
auto operator * (Ts s, Vetor<N, Tv>& v) -> Vetor<N, decltype(v.printable_componentes()[0] * s)> {
  Vetor<N, decltype(v.printable_componentes()[0] * s)> res;
  for(int i=0; i<N; ++i)
    res = v.printable_componentes()[i] * s;
  return res;
}
//Overload do método para permitir comutatividade.
template<int N, typename Ts, typename Tv>
auto operator * (Vetor<N, Tv>& v, Ts s) -> Vetor<N, decltype(v.printable_componentes()[0] * s)> {
  Vetor<N, decltype(v.printable_componentes()[0] * s)> res;
  for(int i=0; i<N; ++i)
    res = v.printable_componentes()[i] * s;
  return res;
}

//Divisão por um escalar, retorna um vetor.
template <int N, typename Ts, typename Tv>
auto operator / (Vetor<N, Tv>& v, Ts s) -> Vetor<N, decltype(v.printable_componentes()[0] / s)>{
  Vetor<N, decltype(v.printable_componentes()[0] / s)> res;
  for(int i=0; i<N; ++i)
    res = v.printable_componentes()[i] / s;;
  return res;
}

//Produto escalar, retorna um numerico.
template<int N, typename Tva, typename Tvb>
auto operator * (Vetor<N,Tva>& va, Vetor<N,Tvb>& vb) -> decltype(va.printable_componentes()[0] * vb.printable_componentes()[0]){
  decltype(va.printable_componentes()[0] * vb.printable_componentes()[0]) res = 0;
  for(int i=0; i<N; ++i)
    res += va.printable_componentes()[i] * vb.printable_componentes()[i];
  return res;
}


//classe para implementar o operador de produto vetorial (**), quando instanciada, retorna retorna o tipo "operação produto vetorial", que quando multiplicado por um vetor efetua a operação propriamente dita.
template <int N, typename Tva>
class prod_vet_opp {
  private:
    Vetor<N, Tva> *_vetor;
    friend class Vetor<N, Tva>;
  public:
    prod_vet_opp( Vetor<N, Tva>& va ): _vetor( &va ) {}
    Tva componente(int axis){
      return _vetor->printable_componentes()[axis] ;
    }  
};

//postergando a operação (**)
template<int N, typename Tv>
prod_vet_opp<N, Tv> operator * (Vetor<N, Tv>& v){
  return prod_vet_opp(v);
}

//produto vetorial, retorna um vetor
template<int N, typename Tv, typename Topp>
auto operator * (Vetor<N, Tv>& v, prod_vet_opp<N, Topp> pv_operation) -> Vetor<N, decltype(v.printable_componentes()[0] * pv_operation.componente(0))>{
  Vetor<N, decltype(v.printable_componentes()[0] * pv_operation.componente(0))> res;
  //produto vetorial
  res = (v.printable_componentes()[1] * pv_operation.componente(2) - pv_operation.componente(1) * v.printable_componentes()[2]);
  res = (v.printable_componentes()[2] * pv_operation.componente(0) - pv_operation.componente(2) * v.printable_componentes()[0]);
  res = (v.printable_componentes()[0] * pv_operation.componente(1) - pv_operation.componente(0) * v.printable_componentes()[1]);
  //todas as componentes do produto vetorial se encontram em res (resultado).
  return res;
}

//Definindo shift de um vetor para output stream.
template<int N,typename T>
ostream& operator << (ostream& o, Vetor<N,T> v) {
  for(int i=0; i<N; ++i)
	  o << v.printable_componentes()[i] << " ";
  return o;
}



int main( int argc, char* argv[]) {     
  Vetor<3,double> v1;
  v1 = 1.3, 2.3, 0;
  Vetor<3, int> v2;
  v2 = 2, 2, 0;
  cout << v1 + v2 + v1 * 2.1 << endl;
  cout << v2 * v1  << endl;
}