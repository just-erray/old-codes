// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<string> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    sort(a[i].begin(), a[i].end());
  }
  sort(a.begin(), a.end());
  int cur = 0;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    if (i == 0 || a[i - 1] != a[i]) {
      ans += 1LL * cur * (cur - 1) / 2;
      cur = 0;
    } 
    ++cur;  
  }
  cout << ans + 1LL * cur * (cur - 1) / 2 << '\n';
}