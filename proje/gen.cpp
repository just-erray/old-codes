// author: erray
#include<bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
int Rand(int l, int r) {
  return uniform_int_distribution(0, r)(rng);
} 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = rng() % 10000 + 1000;
  cout << n << '\n';
  for (int i = 0; i < n; ++i) {
    int t = rng() % 2;
    if (t == 0) {
      cout << "G " << Rand(-1e6, +1e6)  << '\n';
    } else {
      cout << "A " << Rand(-1e6, +1e6) << ' ' << Rand(-1e6, +1e6)  << '\n';
      
    }
  }
}