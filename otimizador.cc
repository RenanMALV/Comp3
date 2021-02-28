#include <tuple>
#include <type_traits>
#include <functional>

using namespace std;

template <int L, int CL, int C>
void mult( double (&res)[L][C], const double (&a)[L][CL], const double (&b)[CL][C] ) {
  for( int i = 0; i < L; i++ )
    for( int j = 0; j < C; j++ )
      res[i][j] = 0;
  
  for( int i = 0; i < L; i++ )
    for( int j = 0; j < C; j++ )
      for( int k = 0; k < CL; k++ )
	res[i][j] += a[i][k] * b[k][j];
}

template <int L, int C>
class Matriz {
  public:
    int size_linha = L;
    int size_coluna = C;
    
    double cell[L][C];
    auto operator [](int i) {return cell[i];}

    Matriz(){};

    template<typename O>
    Matriz(O o) {
      for(int i=0;i<L;++i)
        for(int j=0;j<C;++j)
          cell[i][j] = o[i][j];
    }
    template<typename O>
    Matriz(O& o) {
      for(int i=0;i<L;++i)
        for(int j=0;j<C;++j)
          cell[i][j] = o[i][j];
    }

    template<typename O>
    auto operator = (const O& o) {
      for(int i=0;i<L;++i)
        for(int j=0;j<C;++j)
          cell[i][j] = o[i][j];
      return *this;
    }

};

template <int OL, int OLC, int OC>
class Otimizador {
  public:
    Otimizador(const Matriz<OL, OLC>& a,const Matriz<OLC, OC>& b,int op): a(a), b(b), op(op){}
 
    auto operator [](int i) {
      return res[i];
    }

    auto resultante(){
      multiplica();
      return res;
    }
    
    auto multiplica(){
      mult(res.cell ,a.cell,b.cell);
    }

    template<int mL, int mC>
    auto multiplica(const Matriz<mL, mC>& m){
      if(mL == OC){
        if(OLC*mC < OL*OC){
          Matriz<OLC, mC> temp;
          mult(temp.cell ,b.cell,m.cell);
          mult(res.cell, a.cell, temp.cell);
        }
        else{
          Matriz<OL,OC> temp;
          mult(temp.cell ,a.cell,b.cell);
          mult(res.cell, temp.cell, m.cell);
        }
      }
      /* else if(mL == OLC){
        if(OL*mC < OL*OC){
          Matriz<OL, mC> temp;
          mult(temp.cell , a.cell, m.cell);
          mult(res.cell, temp.cell, b.cell);
        }
        else{
          Matriz<OL,OC> temp;
          mult(temp.cell ,a.cell,b.cell);
          mult(res.cell, temp.cell, m.cell);
        }
      } */
      /* else if(mC == OLC){

      }
      else if(mC == OL){

      } */
      else{
        Matriz<OL,OC> temp;
        mult(temp.cell ,a.cell,b.cell);
        mult(res.cell, temp.cell, m.cell);
      }
      return res;
    }
    
    auto soma(const Matriz< OL, OC >& m){
      for(int i=0;i<OL;++i)
        for(int j=0;j<OC;++j)
          //res[i][j] = m[i][j] + a[i][j] * b[i][j];
      return res;
    }

    
    template <int ML, int MC>
    auto operator = (Matriz<ML,MC> m) { 
      return m;
    }

    Matriz<OL, OLC> a;
    Matriz<OLC, OC> b;  
    int op; // 0 = soma, 1 = mult
    int size_linha = OL;
    int size_coluna = OC;
    Matriz<OL, OC> res;
};

template <int OL, int OC>
class Otimizador<OL, 0, OC> {
  public:
    Otimizador(const Matriz<OL, OC>& a,const Matriz<OL, OC>& b,int op): a(a), b(b), op(op){}
 
    auto operator [](int i) {
      return resultante().cell[i];
    }

    Matriz<OL, OC> resultante(){
      return res;
    }
    
    Matriz<OL, OC> soma(Matriz< OL, OC > m) {
      for(int i=0;i<OL;++i)
        for(int j=0;j<OC;++j)
          res[i][j] = m[i][j] + a[i][j] + b[i][j];
      return res;
    }
    
    template <int ML, int MC>
    auto operator = (Matriz<ML,MC> m) { 
      return m;
    }

    Matriz<OL, OC> a;
    Matriz<OL, OC> b;  
    int op; // 0 = soma, 1 = mult
    int size_linha = OL;
    int size_coluna = OC;
    Matriz<OL, OC> res;
};



template <int L, int LC, int C>
Otimizador< L, LC, C > operator * ( const Matriz<L, LC>& a, const Matriz<LC, C>& b) {
  return Otimizador< L, LC, C >(a, b, 1);
}

template <int L, int LC, int C, int mL, int mC>
auto operator * (  Otimizador<L, LC, C> a, const Matriz<mL, mC>& b) {
  return a.multiplica(b);
}

template <int L, int C>
auto operator + ( const Matriz<L, C>& a, const Matriz<L, C>& b) {
  return Otimizador< L, 0, C >(a, b, 0);
}

template <int L, int C>
Matriz<L,C> operator + ( Otimizador<L, 0, C> a, const Matriz<L, C>& b) {
  return a.soma(b);
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

  template <int OL, int OLC, int OC>
  Matriz<OL,OC> operator()( Otimizador<OL, OLC, OC>& o ) const {
    Matriz<OL,OC> resultante; 
    for(int i=0;i<OL;++i)
      for(int j=0;j<OC;++j)
        resultante[i][j] = f(o[i][j]);
    return resultante;
  }
  
private:
  F f;
};