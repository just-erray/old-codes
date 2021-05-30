// author: erray
#include <bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count()); 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = rng() % 6 + 5; 
  int m = rng() % min(20, n * (n - 1) - 1);
  cout << n << ' ' << m << '\n';
  for (int i = 0; i < m; ++i) {
    int x = rng() % n + 1;
    cout << x << ' ';
    int y = x;
    do {
      y = rng() % n + 1;
    } while (x == y);
    cout << y << ' ';
    cout << rng() % 50 << '\n'; 
  }
}