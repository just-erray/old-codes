// author: erray
#include<bits/stdc++.h>
 
using namespace std;

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }    

  const int LOG = 1 + (int) ceil(__lg(n));
  vector<vector<int>> parent(LOG, vector<int>(n));
  vector<int> depth(n);
  function<void(int)> Dfs_lca = [&](int v) {
    for (auto u : g[v]) {
      if (parent[0][v] == u) {
        continue;
      }

      parent[0][u] = v;
      depth[u] = depth[v] + 1;
      Dfs_lca(u);
    }
  };

  for (int j = 1; j < LOG; ++j) {
    for (int i = 0; i < n; ++i) {
      parent[j][i] = parent[j - 1][parent[j - 1][i]];
    }
  }

  auto LCA = [&](int x, int y) {
    if (depth[x] < depth[y]) {
      swap(x, y);
    }

    int cc = 0, diff = depth[x] - depth[y];
    while (diff > 0) {
      if (diff & 1) {
        x = parent[cc][x];    
      }

      ++cc;
      diff >>= 1;
    }

    for (int t = LOG - 1; t >= 0; --t) {
      if (parent[t][x] != parent[t][y]) {
        x = parent[t][x];
        y = parent[t][y];
      }
    }

    if (x != y) {
      x = parent[0][x];
    }

    return x;
  };

  vector<vector<pair<int, int>> el(n);

  int m;
  cin >> m;
  vector<pair<int, int>> q(m);
  for (int i = 0; i < n; ++i) {
    cin >> q[i].first >> q[i].second;
    --q[i].first;
    --q[i].second;
    int par = LCA(q[i].first, q[i].second);
    if (q[i].first) 
  }
}