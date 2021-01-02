// author: erray
#include<bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = Rand(2, (int) 1e5), k = Rand(2, (int) 1e5);
  cout << n << ' ' << k << '\n';
  for (int i = 0; i < 2 * n; ++i) {
    cout << Rand(1, k) << ' ';
  }
  
}