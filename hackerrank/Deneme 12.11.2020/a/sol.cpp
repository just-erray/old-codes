// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long m, n, a, b;
  cin >> m >> n >> a >> b;
  n -= min(n, m);
  b = min(b, a * 4);
  cout << n / 4 * b + min(a * (n % 4), b) << '\n';
}