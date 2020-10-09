// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ofstream cc("checker_result");
  ifstream in("int");
  //cin is code's output, in is input of the code
  try {
    

      
    
  } catch(const char* c) {
    if (c == "OK") {
      cc << 1;
      cout << "\033[" << 32 << "m" << c << '\n';
    } else {
      cc << 0;
      cout << "\033[" << 31 << "m" << c << '\n';
    }   
  }
  cout << "\037[" << 31 << "m" << '\n';
}