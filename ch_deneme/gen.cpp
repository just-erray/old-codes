// author: erray
#include <bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

int Rand(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
} 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = Rand(3, 10);
  cout << n << '\n';
  for (int i = 0; i < n; ++i) {
    int x = Rand(1, 100);
    int y = Rand(1, 100);
    cout << x << ' ' << y << '\n';
  }

  for (int i = 0; i < n; ++i) {
    cout << Rand(1, 100) << '\n';
  }

}