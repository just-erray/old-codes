// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  long long res = 1;
  for (int i = 2; i <= n; ++i) {
    res *= i / gcd(res, i);
  }
  cout << res + 1 << '\n';
}