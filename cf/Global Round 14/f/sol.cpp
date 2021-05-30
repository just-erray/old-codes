// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    a[i] -= k;
  }
  vector<vector<int>> g(n);
  vector<array<int, 2>> es(m);
  for (int i = 0; i < m; ++i) {
    cin >> es[i][0] >> es[i][1];
    --es[i][0], --es[i][1];
    g[es[i][0]].push_back(i);
    g[es[i][1]].push_back(i);
  }

  if (accumulate(a.begin(), a.end(), 0LL) < 0) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";

}