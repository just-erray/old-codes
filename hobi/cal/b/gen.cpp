// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      cout << rng() % n + 1 << ' ';
    }    
    cout << '\n';
  }
}