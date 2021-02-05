#include <iostream>
#include <type_traits>
#include <vector>
#include <functional>

using namespace std;

class X {
  public:
  template <typename K>
  K operator() ( K valor ) {
    return valor;
  }
  auto operator% ( int div ){
    this->div = div;
    return *this;
  }
  auto operator == (int resto){
    int div = this->div;
    return [div , resto](auto val){return (val % div == resto) ? true: false;};
  }
  int div=2;
}; 


template <typename T> 
class Cte {
public:
  Cte( const T& valor ): valor( valor ) {}

  template<typename K>
  T operator() ( K ignorar ) {
    return valor;
  } 

private:
  T valor;
};

template <typename Op1, typename Op2> 
class Soma {
public:
  Soma(Op1 o1, Op2 o2): a(o1), b(o2) {}
  template<typename K>
  auto operator() ( K valor ) {
      return a( valor ) + b( valor );
  }
private:
  Op1 a;
  Op2 b;
};

template <typename Op1, typename Op2> 
class Mult {
public:
  Mult(Op1 o1, Op2 o2): a(o1), b(o2) {}
  template<typename K>
  auto operator() ( K valor ) {
      return a( valor ) * b( valor );
  }
private:
  Op1 a;
  Op2 b;
};

template <typename Op1, typename Op2>
auto operator + ( Op1 a, Op2 b ) {
  if constexpr( is_same_v< Op1, int> || is_same_v< Op1,const char*> || is_same_v< Op1, double>)
    if constexpr( is_same_v< Op2, int> || is_same_v< Op2,const char*> || is_same_v< Op2, double>)
      return Soma< Cte<Op1>, Cte<Op2> >( Cte<Op1>(a), Cte<Op2>(b) );
    else
      return Soma< Cte<Op1>, Op2 >( Cte<Op1>(a), b);
  else
    if constexpr( is_same_v< Op2, int> || is_same_v< Op2,const char*> || is_same_v< Op2, double>)
      return Soma< Op1, Cte<Op2> >( a, Cte<Op2>(b));
    else
      return Soma< Op1, Op2 >( a, b);  
}

template <typename Op1, typename Op2>
auto operator * ( Op1 a, Op2 b ) {
  if constexpr( is_same_v< Op1, int> || is_same_v< Op1,const char*> || is_same_v< Op1, double>)
    if constexpr( is_same_v< Op2, int> || is_same_v< Op2,const char*> || is_same_v< Op2, double>)
      return Mult< Cte<Op1>, Cte<Op2> >( Cte<Op1>(a), Cte<Op2>(b) );
    else
      return Mult< Cte<Op1>, Op2 >( Cte<Op1>(a), b);
  else
    if constexpr( is_same_v< Op2, int> || is_same_v< Op2,const char*> || is_same_v< Op2, double>)
      return Mult< Op1, Cte<Op2> >( a, Cte<Op2>(b));
    else
      return Mult< Op1, Op2 >( a, b);  
}



template <typename Op1, typename Op2>
auto operator << ( ostream& o, const Mult<Op1,Op2>& opr) { 
 return  [&o,opr]( auto v ) -> ostream& { return o << opr(v); };
}

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

X x;

  int main(){
    //vector<int> v1 = { 1, 2, 3, 4, 1, 1, 0, 8 };
    //v1 | (x % 2 == 0) | cout << x+x;
    //auto s = x + x + 8 + x;
    //cout << s(8);
    //int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
    //vector<int> v;
    //tab | cout << x*x << '\n';
    //tab | [ &v ]( int x ) { v.push_back( x ); };
    //v | x % 2 == 0 | cout << x*x + 1 << '\n';
    //v | x % 2 == 1 | x*x | cout << x << '\n';
    return 0;
  }