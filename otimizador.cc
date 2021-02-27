#include <tuple>
#include <type_traits>
#include <functional>

using namespace std;



template <int L, int C>
class Matriz {
  public:
    int size_linha = L;
    int size_coluna = C;
    double cell[L][C];
    auto operator [](int i) {return cell[i];}
};

template <int L, int LC, int C>
class Otimizador {
  public:
    int size_linha = L;
    int size_coluna = C;
    Matriz< L, LC > a;
    Matriz< LC, C > b;
};

template <int L, int LC, int C>
Otimizador< L, LC, C > operator * ( const Matriz<L,LC>& a, const Matriz<LC,C>& b ) {
}


template <typename F>
class Apply {
public:
  Apply( F f ): f(f) {}
  
  template <int L, int C>
  Matriz<L,C> operator()( Matriz<L,C>& m ) const {
    Matriz<L,C> resultante; 
    for(int i=0;i<L;++i)
      for(int j=0;j<C;++j)
        resultante[i][j] = f(m[i][j]);
    return resultante;
  }
  
private:
  F f;
};