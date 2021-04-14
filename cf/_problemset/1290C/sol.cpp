// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct dsu {
  vector<int> par, sz;
  vector<int> info;
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
  int n, k;
  cin >> n >> k;
  vector<bool> need(n);
  for (int i = 0; i < n; ++i) {
    char c;
    cin >> c;
    need[i] = (c == '1');
  }
  vector<vector<int>> a(k);
  vector<vector<int>> can(n);
  dsu bel(n);
  for (int i = 0; i < k; ++i) {
    int sz;
    cin >> sz;
    a[i].resize(sz);
    for (int j = 0; j < sz; ++j) {
      cin >> a[i][j];
      --a[i][j];
      can[a[i][j]].push_back(i);
      if (j > 0) {
        bel.unite(a[i][j], a[i][j - 1]);
      }
    }
  }
  vector<vector<int>> ls(n);
  for (int i = 0; i < n; ++i) {
    ls[bel.get(i)].push_back(i);
  }
  vector<bool> start(n);
  for (int i = 0; i < n; ++i) {
    if (!ls[i].empty()) {
      start[ls[i][0]] = true;
    }
  }
  assert(start[0]);

}