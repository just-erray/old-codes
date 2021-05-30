// author: erray
#include <bits/stdc++.h>
 
using namespace std;

mt19937_64 rng( chrono::steady_clock::now().time_since_epoch().count()); 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << (uint64_t) rng() << '\n';
}