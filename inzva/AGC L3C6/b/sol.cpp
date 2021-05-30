// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  map<int, int> ct;
  long long ans = 0;
  for (auto e : a) {
    ++ct[e];
    ans += ct[e];
  }
  cout << ans << '\n';
}