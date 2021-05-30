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
  long long cur = 0;
  long long pref = 0;
  long long mx_pref = 0;
  long long ans = 0;
  for (auto e : a) {
    pref += e;
    mx_pref = max(mx_pref, pref);
    ans = max(ans, cur + mx_pref);
    cur += pref;  
  }
  cout << ans << '\n';
}