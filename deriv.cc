#include <type_traits>
#include <math.h>
#include <iostream>
#include <sstream>
#include <functional>

using namespace std;
template <typename E, typename Dx,typename S, typename DS>
struct Par {
    
    string str() const{
      string ret = s();
      return ret;
    }
    string dx_str() const{
      string ret = ds();
      return ret;
    }

    Par(const E& e,const Dx& dx,const S& s,const DS& ds ) : e(e), dx(dx), s(s), ds(ds) {}

    E e;
    Dx dx;
    S s;
    DS ds;
};


inline auto x = Par{ 
    []( double v ) { return v; }, 
    []( double v ) { return 1.0; }, 
    [](){return "x"; },
    [](){return "1"; } 
  }; 

struct X {
    
    string str() const{
      string ret = s();
      return ret;
    }
    string dx_str() const{
      string ret = ds();
      return ret;
    }

    X(){}

    function<double(double)> e = []( double v ) { return v; };
    function<double(double)> dx = []( double v ) { return 1.0; };
    function<string()> s = []() -> string {return "x"; };
    function<string()> ds = []() -> string {return "1"; };
};

template <typename A, typename B, typename C, typename D>
constexpr inline auto trata_cte(const Par<A,B,C,D>& opr ) { 
  return opr;
}

template <typename C>
constexpr inline auto trata_cte(const C& cte ) {
  return  Par{ 
      [cte]( double v ) { return cte; }, 
      []( double v ) { return 0.0; },
      [cte]() { stringstream ret; ret << noshowpoint << cte; return ret.str();},
      []() { return "0"; }
    };
}
auto trata_cte(X cte ) {
  return Par{ 
    []( double v ) { return v; }, 
    []( double v ) { return 1.0; }, 
    [](){return "x"; },
    [](){return "1"; } 
  }; 

}
 
template<typename F, typename G>
constexpr inline auto operator * (const F& f,const G& g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{ 
      [fc, gc]( double v ){ return fc.e(v)*gc.e(v); },
      [fc, gc]( double v ){ return fc.dx(v)*gc.e(v) + fc.e(v)*gc.dx(v); },
      [fc, gc]() { string ret = "((" + fc.str() + ")*(" + gc.str() + "))"; return ret; },
      [fc, gc]() { string ret = "(" + fc.dx_str() + ")*(" + gc.str() + ")+(" + fc.str() + ")*(" + gc.dx_str() + ")"; return ret; }
    };
}

template<typename F, typename G>
constexpr inline auto operator + (const F& f,const G& g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{ 
      [fc, gc]( double v ){ return fc.e(v) + gc.e(v); },
      [fc, gc]( double v ){ return fc.dx(v) + gc.dx(v); },
      [fc, gc]() { string ret = "((" + fc.str() + ")+(" + gc.str() + "))"; return ret; },
      [fc, gc]() { string ret = "((" + fc.dx_str() + ")+(" + gc.dx_str() + "))"; return ret; }
    };
}

template<typename F, typename G>
constexpr inline auto operator - (const F& f,const G& g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{ 
      [fc, gc]( double v ){ return fc.e(v) - gc.e(v); },
      [fc, gc]( double v ){ return fc.dx(v) - gc.dx(v); },
      [fc, gc]() { string ret = "((" + fc.str() + ")-(" + gc.str() + "))"; return ret; },
      [fc, gc]() { string ret = "((" + fc.dx_str() + ")-(" + gc.dx_str() + "))"; return ret; } 
    };
}

template<typename F, typename G>
constexpr inline auto operator / (const F& f,const G& g ) {
    auto fc = trata_cte( f );
    auto gc = trata_cte( g );
    return Par{
      [fc, gc]( double v ){ return fc.e(v) / gc.e(v); },
      [fc, gc]( double v ){ return (fc.dx(v)*gc.e(v) + fc.e(v)*gc.dx(v))/(gc.e(v)*gc.e(v)); },
      [fc, gc]() { string ret = "((" + fc.str() + ")/(" + gc.str() + "))"; return ret; },
      [fc, gc]() { string ret = "(((" + fc.dx_str() + ")*(" + gc.str() + ")-(" + fc.str() + ")*(" + gc.dx_str() + "))/(" + gc.str() + ")^2)"; return ret; }
    };
}

template <typename F, typename G>
constexpr inline auto operator ->* (const F& f,const G& g ) {
    static_assert( !is_same_v< double, G >, "Operador de potenciação definido apenas para inteiros" );

    auto fc = trata_cte( f );
    return Par{ 
      [fc,g]( double v ){ return pow( fc.e(v), g ); },
      [fc,g]( double v ){ return g*fc.dx(v)*pow( fc.e(v), g-1 ); },
      [fc,g]() { string ret = "(" + fc.str() + ")^" + to_string(g); return ret; },
      [fc,g]() { string ret = "(" + to_string(g) + "*(" + fc.dx_str() + ")*(" + fc.str() + ")^" + to_string(g-1) + ")"; return ret; }  
    };
}

template<typename F>
constexpr inline auto sin(const F& f ) {
    auto fc = trata_cte( f );
    return Par{
      [fc]( double v ){ return sin( fc.e(v) ); }, 
      [fc]( double v ){ return cos( fc.e(v) )*fc.dx(v); },
      [fc]() { string ret = "sin(" + fc.str() + ")"; return ret; },
      [fc]() { string ret = "(cos(" + fc.str() + ")*" + fc.dx_str() + ")"; return ret; }  
    };
}

template<typename F>
constexpr inline auto cos(const F& f ) {
    auto fc = trata_cte( f );
    return Par{
      [fc]( double v ){ return cos( fc.e(v) ); }, 
      [fc]( double v ){ return 0 - sin( fc.e(v) )*fc.dx(v); },
      [fc]() { string ret = "cos(" + fc.str() + ")"; return ret; },
      [fc]() { string ret = "(-sin(" + fc.str() + ")*" + fc.dx_str() + ")"; return ret; } 
    };
}

template<typename F>
constexpr inline auto exp(const F& f ) {
    auto fc = trata_cte( f );
    return Par{
      [fc]( double v ){ return exp( fc.e(v) ); }, 
      [fc]( double v ){ return fc.dx(v)*exp( fc.e(v) ); },
      [fc]() { string ret = "exp(" + fc.str() + ")"; return ret; },
      [fc]() { string ret = "(exp(" + fc.str() + ")*(" + fc.dx_str() + "))"; return ret; }  
    };
}

template<typename F>
constexpr inline auto log(const F& f ) {
    auto fc = trata_cte( f );
    return Par{ 
      [fc]( double v ){ return log( fc.e(v) ); }, 
      [fc]( double v ){ return fc.dx(v) / fc.e(v); },
      [fc]() { string ret = "log(" + fc.str() + ")"; return ret; },
      [fc]() { string ret = "(1/" + fc.str() + ")*(" + fc.dx_str() + ")"; return ret; }   
      };
}