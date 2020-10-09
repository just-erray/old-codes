// author: erray
#include<bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = rng() % 20;
  cout << n << '\n';
  for (int i = 0; i < n; ++i) {
    cout  << rng() % (int) 1e9 << '\n';
  }  
}