// author: erray
#include<bits/stdc++.h>
 
using namespace std;

class dsu {
  public:
  vector<int> par, ct;
  dsu(int n) {
    par.resize(n);
    ct.resize(n, 1);
    iota(par.begin(), par.end(), 0);
  }
  inline int get(int v) {
    return par[v] = (v == par[v] ? v : get(par[v]));
  }
  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;
    ct[x] += ct[y];
    par[y] = x;
    return true;
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> mat(n, vector<int>(n, 1037));

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int x;
      cin >> x;
      mat[i][j] = x;
      mat[j][i] = x;
    }
  }
  dsu b(n);
  vector<pair<int, int>> k;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      k.emplace_back(i, j);
    } 
  }

  sort(k.begin(), k.end(), [&](auto x, auto y) {
    return mat[x.first][x.second] < mat[y.first][y.second];
  });

  vector<vector<int>> g(n);
  for (auto[v, u] : k) {
    if (!b.unite(u, v)) {
      continue;
    }
    g[v].push_back(u);
    g[u].push_back(v);
  }
  
  for (int i = 0; i < n; ++i) {
    cout << (int) g[i].size() << ' ';
    sort(g[i].begin(), g[i].end());
    for (auto u : g[i]) {
      cout << u + 1 << ' ';
    }  
    cout << '\n';
  }
}