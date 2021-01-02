// author: erray
#include<bits/stdc++.h>
 
using namespace std;

const int md = (int) 1e9 + 7;

int add(int x, int y) {
  x += y;
  if (x >= md) {
    x -= md;
  }
  assert(x < md);
  return x;
}

int mul(int x, int y) {
  return (1LL * x * y) % md;
} 

int sub(int x, int y) {
  x -= y;
  if (x < 0) {
    x += md;
  }
  assert(x >= 0 && x < md);
  return x;
}

int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) {
      res = mul(res, x);
    }
    x = mul(x, x);
    y >>= 1;
  }

  return res;
}

int inv(int x) {
  return power(y, md - 2);
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);


}