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

    //classe para implementar o operador produto vetorial (**)
    class prod_vet_opp {
      private:
        Vetor *_vetor;
	      prod_vet_opp( Vetor* va ): _vetor( va ) {}
        friend class Vetor;
      public:
	      prod_vet_opp operator * ( T vb ) {
	        cout << "*_vetor pv vb" << endl;
	        return *this;
	      }
	    
    };


    //postergando operador de produto vetorial.
    Vetor<N, T> operator * (prod_vet_opp pv_operation){
      cout << " prod_vet_opp " << endl;
      return this;
    }
    
    prod_vet_opp prod_vet_call(){
      return prod_vet_opp( this );
    }

    //recebe as componentes de um vetor implementado e redireciona para a chamada de função
    T* printable_componentes(){
      return _vetorGeometrico.print_componentes();
    }

    //Adição de vetores, retorna um vetor.
    template<typename Tv>
    auto operator + (Vetor<N,Tv>& v)  -> Vetor<N, decltype(this->printable_componentes()[0] + v.printable_componentes()[0])>{
      Vetor<N, decltype(this->printable_componentes()[0] + v.printable_componentes()[0])> resultante;
      for(int i=0; i<N; ++i)
	      resultante = printable_componentes()[i] + v.printable_componentes()[i];
      return resultante;
    }

    //Subtração de vetores, retorna um vetor.
    template<typename Tv>
    auto operator - (Vetor<N,Tv>& v)  -> Vetor<N, decltype(this->printable_componentes()[0] - v.printable_componentes()[0])>{
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
Vetor<N, Tv>& operator * (Ts s, Vetor<N, Tv>& v){
  for(int i=0; i<N; ++i)
    v = v.printable_componentes()[i] * s;
  return v;
}
//Overload do método para permitir comutatividade.
template<int N, typename Ts, typename Tv>
Vetor<N, Tv>& operator * (Vetor<N, Tv>& v, Ts s){
  for(int i=0; i<N; ++i)
    v = v.printable_componentes()[i] * s;
  return v;
}

//Divisão por um escalar, retorna um vetor.
template <int N, typename Ts, typename Tv>
Vetor<N, Tv>& operator / (Vetor<N, Tv>& v, Ts s){
  for(int i=0; i<N; ++i)
    v = v.printable_componentes()[i] / s;;
  return v;
}

//Produto escalar, retorna um numerico.
template<int N, typename Tva, typename Tvb>
auto operator * (Vetor<N,Tva>& va, Vetor<N,Tvb>& vb) -> decltype(va.printable_componentes()[0] * vb.printable_componentes()[0]){
  decltype(va.printable_componentes()[0] * vb.printable_componentes()[0]) res = 0;
  for(int i=0; i<N; ++i)
    res += va.printable_componentes()[i] * vb.printable_componentes()[i];
  return res;
}

template<int N, typename Tv>
auto operator * (Vetor<N, Tv> v){
return v.prod_vet_call();
}

template<int N, typename Tv, typename pv_op>
Vetor<N, Tv> operator * (Vetor<N, Tv> va, pv_op vb){
cout << "fora da classe *" << endl;
return 0;
}

//Definindo shift de um vetor para output stream.
template<int N,typename T>
ostream& operator << (ostream& o, Vetor<N,T> v) {
  for(int i=0; i<N; ++i)
	  o << v.printable_componentes()[i] << " ";
  return o;
}



int main( int argc, char* argv[]) {     
  Vetor<2,double> v1;
  v1 = 1.5, 2.5;
  Vetor<2, int> v2;
  v2 = 2, 2;
  cout << v1 ** v2 << endl;
  cout << v2/2  << endl;
}