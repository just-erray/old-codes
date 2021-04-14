// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, l;
  cin >> n >> l;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> ct((int) 1e5 + 1);
  for (auto e : a) {
    ++ct[e];
  }

  auto fct = ct;
  for (int i = (int) 1e5; i > 0; --i) {
    ct[i - 1] += ct[i];
  } 
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (ct[i] + min(l, fct[i - 1]) >= i) {
      ans = i;
    }
  }
  cout << ans << '\n';
}