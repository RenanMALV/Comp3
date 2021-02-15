#include <type_traits>
#include <math.h>
#include <iostream>
#include <sstream>
#include <functional>

using namespace std;

class Intervalo{
  public:
    Intervalo(int i, int f): i(i), f(f) {
      v.push_back(i);
    }
    Intervalo(int i): i(i), f(0) {
      v.push_back(i);
    }
    auto begin() const{
      return v.front();
    }
    bool end(){
      if(!f)
        return false;
      else if(v.back()<f)
        return false;
      else
        return true;
    }
    auto next(){
      int nextV = v.back() + 1;
      v.push_back(nextV);
      return v.back();
    }

    vector<int> v;
    int i, f;
};

template <typename V, typename F>
auto operator | ( const V& v, F func ) {
  if constexpr( is_same_v< bool, invoke_result_t< F, decltype( *begin( v ) ) > > ) {
    vector< decay_t< decltype( *begin( v ) ) > > res;
    for( auto x: v )
      if( invoke( func, x ) )
        res.push_back( x );
    return res;
    }
    else if constexpr( is_same_v< void, invoke_result_t< F, decltype( *begin( v ) ) > > ) {
        for( auto x: v )
            func( x );
    }
    else {
        vector< decay_t< invoke_result_t< F, decltype( *begin( v ) ) > > > res;
        
        for( auto x: v )
            res.push_back( invoke( func, x ) );
            
        return res;
    }  
}
template <typename F>
auto operator | ( Intervalo v, F func ) {
  if constexpr( is_same_v< bool, invoke_result_t< F, decltype( v.begin() ) > > ) {
    vector< decay_t< decltype( v.begin() ) > > res;
    for( auto it = v.begin(); !v.end(); it = v.next())
      if( invoke( func, it ) ){
        res.push_back( it );
      }
    return res;
    }
    else if constexpr( is_same_v< void, invoke_result_t< F, decltype( v.begin() ) > > ) {
      for( auto it = v.begin(); !v.end(); it = v.next())
        func( it );
    }
    else {
      vector< decay_t< invoke_result_t< F, decltype( v.begin() ) > > > res;
      for( auto it = v.begin(); !v.end(); it = v.next())
        res.push_back( invoke( func, it ) );
      return res;
    }  
}
