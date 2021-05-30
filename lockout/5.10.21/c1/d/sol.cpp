// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct dsu {
  vector<int> par, sz;
  dsu(int n) {
    par.resize(n);
    sz.resize(n, 1);
    iota(par.begin(), par.end(), 0);
  }
  inline int get(int v) {
    return par[v] = (v == par[v] ? v : get(par[v]));
  }
  int size(int v) {
    return sz[get(v)];
  }
  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;
    sz[x] += sz[y];
    par[y] = x;
    return true;
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> g(n);
  dsu bel(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    bel.unite(x, y);
    g[x].push_back(y);
    g[y].push_back(x);
  }  
  for (int i = 0; i < k; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }  

  for (int i = 0; i < n; ++i) {
    int ans = bel.size(i);
    for (auto u : g[i]) {
      ans -= (bel.get(u) == bel.get(i));
    }
    cout << ans - 1 << ' ';
  }
  
}