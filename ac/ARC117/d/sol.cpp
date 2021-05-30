// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  
  vector<int> d(n);
  vector<int> par(n);
  function<void(int, int)> Dfs = [&](int v, int pr) {
    par[v] = pr;
    for (auto u : g[v]) {
      if (u == pr) {
        continue;
      }
      d[u] = d[v] + 1;
      Dfs(u, v);
    }  
  };
  Dfs(0, -1);
  int start = int(max_element(d.begin(), d.end()) - d.begin());
  d.assign(n, 0);
  Dfs(start, -1);
  int end = int(max_element(d.begin(), d.end()) - d.begin());
  par[start] = -1;

  vector<bool> last(n);
  {
    int v = end;
    while (v > -1) {
      last[v] = true;
      v = par[v];
    }
  }
  int cur = 0;
  vector<int> ans(n);
  function<void(int, int)> Dfs2 = [&](int v, int pr) {
    ans[v] = ++cur;
    int store = -1;
    for (auto u : g[v]) {
      if (u == pr) {
        continue;
      }
      if (last[u]) {
        store = u;
      } else {
        Dfs2(u, v);
      }
    }
    if (store != -1) {
      Dfs2(store, v);
    }
    ++cur;
  };
  Dfs2(start, -1);
  for (auto e : ans) {
    cout << e << ' ';
  }
}
