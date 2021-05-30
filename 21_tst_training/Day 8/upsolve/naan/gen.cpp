// author: erray
#include <bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count()); 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  auto Rand = [&](int x, int y) {
    return uniform_int_distribution<int>(x, y)(rng);
  };

  int n = Rand(1, 6);
  int l = Rand(1, 100);
  cout << n << ' ' << l << '\n';
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < l; ++j) {
      cout << Rand(1, 10) << ' ';
    }
    cout << '\n';
  }
}