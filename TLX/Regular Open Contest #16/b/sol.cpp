// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  if ((int) a.size() == 1) {
    return cout << 0, 0;
  }
  int ans = m - a.back() + a[0];
  for (int i = 1; i < (int) a.size(); ++i) {
    ans = max(ans, a[i] - a[i - 1]);
  }
  cout << m - ans << '\n';
}