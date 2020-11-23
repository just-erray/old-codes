// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T> class graph {
  public:
  struct edge {
    int v, u;
    T w;
  };

  int n;
  vector<vector<int>> g;
  vector<edge> edges;

  graph(int _n) : n(_n) {
    g.resize(n);
  }

  graph(const graph<T>& _g) {
    n = _g.n;
    g = _g.g;
    edges = _g.edges;
  }

  graph() { }

  void clear() {
    n = 0;
    g.clear();
    edges.clear();
  }

  virtual int add(int v, int u, T w = 1) = 0;
};

template<typename T> class undigraph : public graph<T> {
  public:
  using graph<T>::n;
  using graph<T>::g;
  using graph<T>::edges;

  undigraph(int _n) : graph<T>(_n) { }

  undigraph(const undigraph<T>& _g) : graph<T>() {
    n = _g.n;
    g = _g.g;
    edges = _g.edges;
  }

  int add(int v, int u, T w = 1) {
    assert(v >= 0 && u >= 0 && v < n && u < n);
    int id = (int) edges.size();
    g[v].push_back(id);
    g[u].push_back(id);
    edges.push_back({v, u, w});
    return id;
  }
};

template<typename T> vector<T> djikstra(const undigraph<T>& g, int sv) {
  assert(sv < g.n);
  vector<T> res(g.n, numeric_limits<T>::max());
  vector<bool> vis(g.n);
  priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
  pq.emplace(0, sv);
  res[sv] = 0;
  while (!pq.empty()) {
    int v;
    T cost;
    tie(cost, v) = pq.top();
    pq.pop();
    if (vis[v]) {
      continue;
    }
    vis[v]  = true;
    for (auto id : g.g[v]) {
      int nxt = g.edges[id].u ^ g.edges[id].v ^ v;
      T nCost = cost + g.edges[id].w;
      if (vis[nxt] || res[nxt] < nCost) {
        continue;
      }
      res[nxt] = nCost;
      pq.emplace(nCost, nxt);
    }
  }
  return res;
}

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
  int n, m, k;
  cin >> n >> m >> k;
  dsu d(n);
  vector<int> id(n);
  int lst = 0;
  for (int i = 0; i < k; ++i) {
    int x;
    cin >> x;
    while (x--) {
      id[lst] = i;
      ++lst;
    }
  }  
  undigraph<long long> g(k);
  for (int i = 0; i < m; ++i) {
    int x, y, w;
    cin >> x >> y >> w;
    --x, --y;
   if (w == 0) {
      d.unite(x, y);
    }
    if (id[x] != id[y]) {
      g.add(id[x], id[y], w);
    }
  }
  bool ok = true;
  for (int i = 0; i < n - 1; ++i) {
   ok &= (id[i] != id[i + 1] || d.get(i) == d.get(i + 1));    
  }
  if (!ok) {
    return cout << "No\n", 0;
  }
  cout << "Yes\n";
  for (int i = 0; i < k; ++i) {
    for (auto el : djikstra(g, i)) {
      cout << (el == LLONG_MAX ? -1 : el) << ' ';
    }
    cout << '\n';
  }
}