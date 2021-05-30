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
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  dsu d(n);
  while (m--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    d.unite(x, y);
  }
  vector<long long> tot(n);
  for (int i = 0; i < n; ++i) {
    tot[d.get(i)] += a[i] - b[i];
  }
  bool ok = true;
  for (int i = 0; i < n; ++i) {
    ok &= (tot[i] == 0);
  }
  cout << (ok ? "Yes" : "No") << '\n';
}
