// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  map<int, int> ct;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    ++ct[x];
  } 

  int ans = -1;
  int f = 0;
  for (auto[id, x] : ct) {
    if (x % k != 0) {
      ++f;
      ans = id;
    }
  }

  assert(f == 1);
  cout << ans << '\n';
}