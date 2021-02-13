#include <iostream>
#include <functional>
#include <initializer_list>

using namespace std;

/*template<typename F, typename... Args_t1, typename... Args_t2>
class bind{
  public:
    //Constructor
    bind(F func, Args_t1... args_t1, Args_t2... args_t2){
      
    }

  private:

};*/

//Numero variável de argumentos de um só tipo

template <size_t I = 0, typename... Ts> 
constexpr void printTuple(tuple<Ts...> tup) 
{ 
    // If we have iterated through all elements 
    if
        constexpr(I == sizeof...(Ts)) 
        { 
            // Last case, if nothing is left to 
            // iterate, then exit the functiopn 
            return; 
        } 
    else { 
        // Print the tuple and go to next element 
        cout << get<I>(tup) << " "; 
  
        // Going for next element. 
        printTuple<I + 1>(tup); 
    } 
} 


template<typename F, typename... Args>
class bind{
  public:
    //Constructor
    bind(F func, Args... args): func(func), args(forward<Args>(args)...){
      //se invocavel retorna o resultado
      //if constexpr(is_invocable_v<F, Args...>){}
    }

    template <typename... Ts>
    void catArg(tuple<Ts...> tup){
      args = tup;
    }

    template <typename... Ts>
    bool constexpr IsBinded(tuple<Ts...> tup){
      if constexpr(is_invocable_v<F, Ts...>){
        return true;
      }
      else
        return false;
    }
    
    //chama recursivamente outro bind
    template<typename... Functor_args>
    auto operator() ( Functor_args... Fargs){
      auto newArgs = tuple_cat(args, make_tuple( forward<Functor_args>(Fargs)... ));

      printTuple(newArgs);
      
      if (IsBinded(newArgs)){
        return invoke( func&, newArgs );
      }
      else{
        catArg(newArgs);
        return *this;
      }
    }
    

    F func;
    tuple<Args...> args;
  private:
};


