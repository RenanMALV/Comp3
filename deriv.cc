#include <type_traits>
#include <math.h>
#include <iostream>

using namespace std;

template <typename E, typename Dx>
struct Par {
    const E e;
    const Dx dx;

    constexpr Par( E e, Dx dx ) : e(e), dx(dx) {}
};

constexpr inline auto x = Par{ []( double v ) { return v; }, []( double v ) { return 1.0; } }; 

template <typename A, typename B>
constexpr inline auto trata_cte( Par<A,B> opr ) { 
  return opr;
}

template <typename C>
constexpr inline auto trata_cte( C cte ) { 
  return Par{ [cte]( double v ) { return cte; }, []( double v ) { return 0.0; } };
}

template<typename F, typename G>
constexpr inline auto operator * ( F f, G g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{ [fc,gc]( double v ){ return fc.e(v)*gc.e(v); },
                [fc,gc]( double v ){ return fc.dx(v)*gc.e(v) + fc.e(v)*gc.dx(v); } };
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