// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int x, y, l;
    cin >> x >> y >> l;
    --x, --y, --l;
    g[x].emplace_back(y, l);
    g[y].emplace_back(x, l);
  }
           
  vector<int> ans(n, -1);
  vector<bool> vis(n);
  function<void(int, int, bool)> Dfs = [&](int v, int from, bool taken) {
    if (!taken) {
      ans[v] = from; 
    } else {
      ans[v] = (from == 0);    
    }
    vis[v] = true;
    for (auto[u, c] : g[v]) {
      if (vis[u]) {
        continue;
      }
      Dfs(u, c, (ans[v] == c));
    }
  };
  Dfs(0, 0, false);

  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
}