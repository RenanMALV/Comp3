#include <type_traits>
#include <math.h>
#include <iostream>
#include <sstream>

using namespace std;

template <typename E, typename Dx,typename S>
struct Par {
    
    string str() const{
      string ret = s();
      return ret;
    }
    string dx_str() const{
      string ds = "test ds";
      return ds;
    }

    constexpr Par( E e, Dx dx, S s ) : e(e), dx(dx), s(s) {}

    const E e;
    const Dx dx;
    const S s;
};

constexpr inline auto x = Par{ 
    []( double v ) { return v; }, 
    []( double v ) { return 1.0; }, 
    [](){string s = "x"; return s; } 
  }; 

template <typename A, typename B, typename C>
constexpr inline auto trata_cte( Par<A,B,C> opr ) { 
  return opr;
}

template <typename C>
constexpr inline auto trata_cte( C cte ) { 
  return Par{ 
      [cte]( double v ) { return cte; }, 
      []( double v ) { return 0.0; },
      [cte]() { stringstream ret; ret << noshowpoint << cte; return ret.str(); } 
    };
}

template<typename F, typename G>
constexpr inline auto operator * ( F f, G g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{ 
      [fc,gc]( double v ){ return fc.e(v)*gc.e(v); },
      [fc,gc]( double v ){ return fc.dx(v)*gc.e(v) + fc.e(v)*gc.dx(v); },
      [fc,gc]() { string ret = "((" + fc.str() + ")*(" + gc.str() + "))"; return ret; }
    };
}

template<typename F, typename G>
constexpr inline auto operator + ( F f, G g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{ [fc,gc]( double v ){ return fc.e(v) + gc.e(v); },
                [fc,gc]( double v ){ return fc.dx(v) + gc.dx(v); } };
}

template<typename F, typename G>
constexpr inline auto operator - ( F f, G g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{ [fc,gc]( double v ){ return fc.e(v) - gc.e(v); },
                [fc,gc]( double v ){ return fc.dx(v) - gc.dx(v); } };
}

template<typename F, typename G>
constexpr inline auto operator / ( F f, G g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{ [fc,gc]( double v ){ return fc.e(v) / gc.e(v); },
                [fc,gc]( double v ){ return (fc.dx(v)*gc.e(v) + fc.e(v)*gc.dx(v))/(gc.e(v)*gc.e(v)); } };
}

template <typename F, typename G>
constexpr inline auto operator ->* ( F f, G g ) {
    static_assert( !is_same_v< double, G >, "Operador de potenciação definido apenas para inteiros" );

    auto fc = trata_cte( f );
    return Par{ [fc,g]( double v ){ return pow( fc.e(v), g ); },
                [fc,g]( double v ){ return g*fc.dx(v)*pow( fc.e(v), g-1 ); } };
}

template<typename F>
constexpr inline auto sin( F f ) {
    auto fc = trata_cte( f );
    return Par{ [fc]( double v ){ return sin( fc.e(v) ); }, 
                [fc]( double v ){ return cos( fc.e(v) )*fc.dx(v); } };
}

template<typename F>
constexpr inline auto cos( F f ) {
    auto fc = trata_cte( f );
    return Par{ [fc]( double v ){ return cos( fc.e(v) ); }, 
                [fc]( double v ){ return 0 - sin( fc.e(v) )*fc.dx(v); } };
}

template<typename F>
constexpr inline auto exp( F f ) {
    auto fc = trata_cte( f );
    return Par{ [fc]( double v ){ return exp( fc.e(v) ); }, 
                [fc]( double v ){ return fc.dx(v)*exp( fc.e(v) ); } };
}

template<typename F>
constexpr inline auto log( F f ) {
    auto fc = trata_cte( f );
    return Par{ [fc]( double v ){ return log( fc.e(v) ); }, 
                [fc]( double v ){ return fc.dx(v) / fc.e(v); } };
}