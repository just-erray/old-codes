// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    a[i] -= min(i, n - i - 1);
  }
  sort(a.begin(), a.end());
  int ans = 0;
  int ct = 1;
  for (int i = 1; i < n; ++i) {
    if (a[i] != a[i - 1]) {
      if (a[i - 1] > 0) {
        ans = max(ans, ct);
      }
      ct = 0;
    }  
    ++ct;
  }
  cout << n - max(ans, (a.back() > 0 ? ct : 0)) << '\n';
  
}