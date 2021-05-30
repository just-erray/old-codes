// author: erray
#include <bits/stdc++.h>
 
using namespace std;

int ex_gcd(int a, int b, int& x, int& y) {
  if (a < b) {
    swap(a, b);
  }
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int d = ex_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

pair<int, int> CRT(vector<pair<int, int>> a) {
  pair<int, int> res = a[0];
  for (int i = 1; i < int(a.size()); ++i) {
    auto[a1, n1] = res;
    auto[a2, n2] = a[i];
    //n1 * x - n2 * y = d
    int x, y;
    int d = ex_gcd(n1, n2, x, y);
    //n1 * x * (a2 - a1) / d - n2 * y * (a2 - a1) / d = a2 - a1
    res.second = n1 / d * n2;
    res.first = n1 / d * x * (a2 - a1) + a1;
  }
  return res;
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}