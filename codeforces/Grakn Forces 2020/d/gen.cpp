// author: erray
#include<bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = (int) 2e4;
  const int N = (int) 1e6;
  for (int i = 0; i < n * 2; ++i) {
    cout << rng() % N << ' ' << rng() % N << '\n';
  }
}