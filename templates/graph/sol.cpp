// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T, typename F> string to_string(pair<T, F> p);
template<typename T, typename F, typename Tr> string to_string(tuple<T, F, Tr> p);
template<typename T, typename F, typename Tr, typename Th> string to_string(tuple<T, F, Tr, Th> p);
string to_string(string s) {
  return '"' + s + '"';
}
string to_string(char c) {
  return (string) "'" + c + "'";
}
string to_string(const char* p) {
  return to_string((string) p);
}
string to_string(bool B) {
  return (B ? "true" : "false");
}
string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if ((int) res.size() > 1) res += ", ";
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
template<size_t T> string to_string(bitset<T> bs) {
  return bs.to_string();
}
template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& el : v) {
    if ((int) res.size() > 1) res += ", ";
    res += to_string(el);
  }
  res += "}";
  return res;
}
template<typename T, typename F> string to_string(pair<T, F> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename T, typename F, typename Tr> string to_string(tuple<T, F, Tr> p) {
  return '(' + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ')';
}
template<typename T, typename F, typename Tr, typename Th> string to_string(tuple<T, F, Tr, Th> p) {
    return '(' + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ')';
}
void debug_out() {
  cerr << endl;
}
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" , debug_out(__VA_ARGS__)
#else
#define debug(...) (void) 37
#endif


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
 
template<typename T> class forest : public graph<T> {
  public:    
  using graph<T>::n;  
  using graph<T>::g;
  using graph<T>::edges;
  
  forest(int _n) : graph<T>(_n) { }
 
  forest(const forest<T>& _g) : graph<T>() {
    n = _g.n;
    g = _g.g;
    edges = _g.edges;   
  }

  int add(int v, int u, T w = 1) {
    assert(v >= 0 && u >= 0 && v < n && u < n);
    int id = (int) edges.size();
    assert(id < n - 1);
    g[v].push_back(id);
    g[u].push_back(id);
    edges.push_back({v, u, w});
    return id;
  }
};


template<typename T> class dfs_forest : public forest<T> {
  public:
  using forest<T>::n;  
  using forest<T>::g;
  using forest<T>::edges;

  vector<int> depth, parent, root, sz, edge, order;
  vector<T> dist;

  void clear() {
    depth.clear();
    parent.clear();
    root.clear();
    sz.clear();
    edge.clear();
    depth.clear();
    dist.clear();
    order.clear();
  }

  void init() {
    depth.resize(n, 0);
    parent.resize(n, -1);
    root.resize(n, -1);
    sz.resize(n, 1);
    edge.resize(n, -1);
    depth.resize(n, 0);
    dist.resize(n, T{});
  }

  private:
  void Dfs(int v) {
    order.push_back(v);
    for (auto id : g[v]) {
      auto e = edges[id];
      int nxt = e.u ^ e.v ^ v;
      if (nxt == parent[v]) {
        continue;
      }
      depth[nxt] = depth[v] + 1;
      parent[nxt] = v;
      root[nxt] = root[v];
      edge[nxt] = id;
      dist[nxt] = dist[v] + e.w;
      Dfs(nxt);
      sz[v] += sz[nxt];
    }
  }

  void root_dfs(int v) {
    root[v] = v;
    Dfs(v);
  }


  public:
  void dfs(int v) {
    if (depth.empty()) {
      init();
    }
    root_dfs(v);
  }
  
  void dfs_all() {
    if (order.empty()) {
      init();
    }
    for (int i = 0; i < n; ++i) {
      if (parent[i] == -1) {
        root_dfs(i);
      }
    }    
  }

  dfs_forest(int _n) : forest<T>(_n) { }

  dfs_forest(const forest<T> _g) : forest<T>(_g) { }
  
};


template<typename T> class lca_lift : public dfs_forest<T> {
  public:    
  using dfs_forest<T>::n;  
  using dfs_forest<T>::edges;
  using dfs_forest<T>::depth;
  using dfs_forest<T>::parent;
  using dfs_forest<T>::dfs;
  using dfs_forest<T>::edge;

  int lg = -1;
  vector<vector<int>> mat;

  void clear() {
    mat.clear();
    lg = -1;    
  }

  private:
  void init() {
    lg = 32 - __builtin_clz(n);
    mat.resize(lg, vector<int>(n));
  }

  public:
  void build(int r = 0) {
    dfs(r);
    mat[0] = parent;
    mat[0][r] = r;
    for (int j = 1; j < lg; ++j) {
      for (int i = 0; i < n; ++i) {
        mat[j][i] = mat[j - 1][mat[j - 1][i]];
      }
    }
  }
  
  int get(int v, int u) {
    if (depth[u] > depth[v]) {
      swap(v, u);
    }
    int f = depth[v] - depth[u];
    int up = 0;
    while (f) {
      if (f & 1) {
        v = mat[up][v];  
      }
      f >>= 1;
      ++up;
    }
    for (int j = lg - 1; j >= 0; --j) {
      if (mat[j][u] != mat[j][v]) {
        v = mat[j][v];
        u = mat[j][u];
      }
    }
    if (u != v) {
      v = mat[0][v];
    }
    return v;
  }
  
  lca_lift(forest<T> x) : dfs_forest<T>(x) {
    init();
  }

  lca_lift(int _n) : dfs_forest<T>(_n) {
    init();
  }

};

template<typename T, typename M, typename F = function<T(const T&, const T&)>> 
class lift : public lca_lift<M> {
  public:
  using lca_lift<M>::n;
  using lca_lift<M>::edges;
  using lca_lift<M>::depth;
  using lca_lift<M>::mat;
  using lca_lift<M>::build;    
  using lca_lift<M>::edge;

  int l = -1;
  vector<vector<T>> t;
  F cal = nullptr;
  T def;

  void clear() {
    t.clear();
    l = -1;
    cal = nullptr;
  }

  void init() {
    l = 32 - __builtin_clz(n);
    t.resize(l, vector<T>(n));
  }

  void build() {
    vector<T> res(n, def);
    build(0);
    for (int i = 0; i < n; ++i) {
      if (edge[i] == -1) {
        continue;
      }
      res[i] = edges[edge[i]].w;
    }
    build(res);
  }
  
  void build(vector<T> values) {
    if (mat[0][0] == -1) {
      build(0);  
    }
    t[0] = values;
    for (int j = 1; j < l; ++j) {
      for (int i = 0; i < n; ++i) {
        int par = mat[j - 1][i];
        t[j][i] = cal(t[j - 1][i], t[j - 1][par]);
      }  
    }
  }

  T get(int v, int u, bool node = false) {
    T res = def;
    if (depth[v] < depth[u]) {
      swap(v, u);
    }
    int f = depth[v] - depth[u];
    int up = 0;
    while (f) {
      if (f & 1) {
        res = cal(res, t[up][v]);
        v = mat[up][v];  
      }
      f >>= 1;
      ++up;
    }
    for (int j = l - 1; j >= 0; --j) {
      if (mat[j][u] != mat[j][v]) {
        res = cal(res, t[j][v]);
        res = cal(res, t[j][u]);
        v = mat[j][v];
        u = mat[j][u];
      }
    }
    if (u != v) {
      res = cal(t[0][v], res);
      res = cal(t[0][u], res);
      v = u = mat[0][v];
    }
    if (node) {
      // if values are on nodes, not edges
      res = cal(res, t[0][v]);
    }
    return res;
  }

  lift(int _n, T _def, F _cal) : lca_lift<M>(_n), def(_def), cal(_cal) {
    init();        
  }

  lift(forest<M> f, T _def, F _cal) : lca_lift<M>(f), def(_def), cal(_cal) {
    init();    
  }

};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  forest<int> f(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y, w;
    cin >> x >> y >> w;
    --x, --y;
    f.add(x, y, w);
  }  
  lift<long long, int> l(f, 0, [&](auto x, auto y) {
    return x + y;
  });
  l.build();
  int m;
  cin >> m;
  while (m--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    cout << l.get(x, y) << '\n';
  }
}