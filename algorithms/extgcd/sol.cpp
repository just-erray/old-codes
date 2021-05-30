// author: erray
#include <bits/stdc++.h>
 
using namespace std;

int extgcd(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int p = a / b;
  int d = extgcd(b, a - b * p, y, x);
  x -= y * p;
  return d;
}

bool crt(int a1, int n1, int a2, int n2, long long& res) {
  if (n1 > n2) {
    swap(n1, n2);
    swap(a1, a2);
  }
  int x, y;
  int d = extgcd(n1, n2, x, y);
  res = a1 + n1 / d * x * (a2 - a1);
  return (res % n2 == a2);
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}