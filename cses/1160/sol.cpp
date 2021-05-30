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
  int n, q;
  cin >> n >> q;
  vector<int> g(n);
  for (int i = 0; i < n; ++i) {
    cin >> g[i];
    --g[i];
  }

  vector<int> root(n, -1);
  function<void(int, int)> Dfs = [&](int v) {
    
  };

  dsu d(n);
  for (int i = 0; i < n; ++i) {
    if (!d.unite(i, g[i])) {
      Dfs(i);
    }
  }

}