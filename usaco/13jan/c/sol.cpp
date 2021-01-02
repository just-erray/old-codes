// author: erray
#include<bits/stdc++.h>
 
using namespace std;

class dsu {
  public:
  vector<int> par;
  dsu(int n) {
    par.resize(n);
    iota(par.begin(), par.end(), 0);
  }  

  inline int get(int v) {
    return par[v] = (v == par[v] ? v : get(par[v]));    
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;
    par[y] = x;
    return true;  
  }
};

 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "skilevel";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, m, t;
  cin >> n >> m >> t;
  vector<vector<int>> mat(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }

  auto hash = [&](int x, int y) {
    return x * m + y;
  };
  
  vector<array<int, 3>> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i > 0) {
        edges.push_back({abs(mat[i][j] - mat[i - 1][j]), hash(i, j), hash(i - 1, j)});  
      }

      if (j > 0) {
        edges.push_back({abs(mat[i][j] - mat[i][j - 1]), hash(i, j), hash(i, j - 1)});  
      }
    }
  }
  sort(edges.begin(), edges.end());

  const int N = n * m;
  vector<int> info(N, 1);
  vector<int> ans(N, -1);
  vector<bool> ok(N, false);
  dsu d(N);

  for (int i = 0; i < (int) edges.size(); ++i) {
    int w = edges[i][0], u = edges[i][1], v = edges[i][2];

    v = d.get(v);
    u = d.get(u);
    if (ok[v] && ok[u]) {
      continue;
    }

    if (ok[u]) {
      swap(u, v);
    }

    if (ok[v]) {
      ok[u] = true;
      ans[u] = w;
      continue;
    }

    if (d.unite(v, u)) {
      info[v] += info[u];
      if (info[v] >= t) {
        ok[v] = true;
        ans[v] = w;
      }
    }
  }

  long long r = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x;
      cin >> x;
      if (x) {
        r += ans[d.get(hash(i, j))];
      }
    }
  }
  cout << r << '\n';
}