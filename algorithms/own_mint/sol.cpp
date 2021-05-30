// author: erray
#include <bits/stdc++.h>
 
using namespace std;

template<typename A, typename B> 
A inverse(A x, B m) {
  m -= 2;
  A res = 1;
  while (m > 0) {
    if (m & 1) {
      res *= x;
    }
    x *= x;
    m >>= 1;
  }
  return res;
}

struct 
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}