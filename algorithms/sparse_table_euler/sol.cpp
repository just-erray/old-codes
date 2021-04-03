// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T, typename F = function<T(const T&, const T&)>> class SparseTable {
  public:
  int sz, lg;
  vector<vector<T>> table;
  F cal;
  SparseTable() { }
  SparseTable(vector<T> v, F _cal) : cal(_cal) {
    sz = (int) v.size();
    lg = 32 - __builtin_clz(sz);
    table.resize(lg);
    table[0] = v;
    for (int i = 1; i < lg; ++i) {
      table[i].resize(sz - (1 << i) + 1);
      assert(sz - (1 << i) + 1 >= 0);
      for (int j = 0; j < (int) table[i].size(); ++j) {
        table[i][j] = cal(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  T get(int l, int r) {
    assert(l >= 0 && r < sz && l <= r);
    int clg = 31 - __builtin_clz(r - l + 1);
    return cal(table[clg][l], table[clg][r - (1 << clg) + 1]);
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<int> tour;
  vector<array<int, 2>> pos(n);
  vector<int> d(n);
  function<void(int, int)> Dfs = [&](int v, int pr) {
    pos[v][0] = pos[v][1] = (int) tour.size();
    tour.push_back(v);
    for (auto u : g[v]) {
      if (u == pr) {
        continue;
      }

      d[u] = d[v] + 1;
      Dfs(u, v);
      pos[v][1] = (int) tour.size();
      tour.push_back(v);
    }
  };
  Dfs(0, -1);
  SparseTable st(tour, [&](int x, int y) {
    return (d[x] < d[y] ? x : y);
  });
  auto LCA = [&](int x, int y) {
    if (pos[x][0] > pos[y][0]) {
      swap(x, y);
    }

    if (pos[x][1] >= pos[y][1]) {
      return x;
    }

    return st.get(pos[x][1], pos[y][0]);
  };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << i + 1 << ' ' << j + 1 << ' ' << LCA(i, j) + 1 << '\n';
    }
  }
 }
