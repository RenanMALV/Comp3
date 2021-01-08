#include <vector>
#include <iostream>

using namespace std;

template<typename T, >
T operator | (  ) {
      ;
      return ;
    }

int main( int argc, char* argv[]) {     

  int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
  vector<int> v{ 2 , 6, 8 };
  tab | []( int x ) { cout << x*x << endl; };
  tab | [ &v ]( int x ) { v.push_back( x ); };
  v | []( int x ) { cout << x*x << endl; };
  v | &print;
}