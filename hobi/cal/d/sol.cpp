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

  int d = 0;
  for (auto e : a) {
    d = __gcd(d, e);
  }
  string ans;
  for (auto e : a) {
    ans += to_string(e - d);
  }
  int p = 0;
  while (p < int(ans.size() - 1) && ans[p] == '0') {
    ++p;
  }
  ans.erase(ans.begin(), ans.begin() + p);
  cout << ans << '\n';
}