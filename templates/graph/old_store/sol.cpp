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

template<typename T> class digraph : public graph<T> {
  public:    
  using graph<T>::n;  
  using graph<T>::g;
  using graph<T>::edges;

  digraph(int _n) : graph<T>(_n) { }
  
  digraph(const digraph<T>& _g) : graph<T>() {
    n = _g.n;
    g = _g.g;
    edges = _g.edges;
  }

  int add(int v, int u, T w = 1) {
    assert(v >= 0 && u >= 0 && v < n && u < n);
    int id = (int) edges.size();
    g[v].push_back(id);
    g[u].push_back(id); //for reverse edges
    edges.push_back({v, u, w});
    return id;
  }

  void reverse() {
    for (auto& el : edges) {
      swap(el.u, el.v);
    }
  }
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

template<typename T> vector<int> top_sort(const digraph<T>& g) {
  vector<int> deg(g.n);
  for (int i = 0; i < (int) g.edges.size(); ++i) {
    ++deg[g.edges[i].u];
  }
  queue<int> q;
  vector<int> res;
  res.reserve(g.n);
  for (int i = 0; i < g.n; ++i) {
    if (deg[i] == 0) {
      q.push(i);
    }        
  }
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    res.push_back(v);
    for (auto id : g.g[v]) {
      if (g.edges[id].v == v) {
        int u = g.edges[id].u;
        if (--deg[u] == 0) {
          q.push(u);
        }
      }
    } 
  }
  return res;
}

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

template<typename T> vector<T> djikstra_set(const undigraph<T>& g, int sv) {
  assert(sv < g.n);
  vector<T> res(g.n, numeric_limits<T>::max());
  vector<bool> vis(g.n);
  set<pair<T, int>> pq;
  pq.emplace(0, sv);
  res[sv] = 0;
  while (!pq.empty()) {
    int v;
    T cost;
    tie(cost, v) = *pq.begin();
    pq.erase(pq.begin());
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

template<typename T> vector<T> djikstra_sq(const undigraph<T>& g, int sv) {
  assert(sv < g.n);
  vector<T> res(g.n, numeric_limits<T>::max());
  vector<bool> vis(g.n);
  queue<int> q;  
  res[sv] = 0;
  q.push(sv);
  vector<vector<T>> mat(g.n, vector<T>(g.n, -1));
  for (auto[v, u, w] : g.edges) {
   mat[u][v] = w;
   mat[v][u] = w;
  }
  int v = sv;
  while (v != -1) {
    vis[v] = true;
    int next_v = -1;
    T next_cost = numeric_limits<T>::max();
    for (int i = 0; i < g.n; ++i) {
      if (mat[v][i] != -1) {
        res[i] = min(res[i], res[v] + mat[v][i]); 
      }
      if (!vis[i] && res[i] < next_cost) {
        next_cost = res[i];
        next_v = i;
      }
    }
    v = next_v;
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

template<typename T> vector<int> mst(const forest<T>& g) {
  vector<int> res;
  vector<int> ord(g.n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int x, int y) {
    return g.edges[x].w < g.edges[y].w;
  });
  dsu d(g.n);
  for (auto id : ord) {
    if (d.unite(g.edges[id].v, g.edges[id].u)) {
      res.push_back(id);  
    }
  }
  return res;
}

template<typename T> class dfs_tree : public undigraph<T> {
  public:
  using undigraph<T>::n;  
  using undigraph<T>::g;
  using undigraph<T>::edges;

  vector<int> depth, parent, root, sz, edge, back, child, order;
  vector<T> dist;
  vector<bool> is_back;

  void clear() {
    depth.clear();
    parent.clear();
    root.clear();
    sz.clear();
    edge.clear();
    depth.clear();
    dist.clear();
    back.clear();
    child.clear();
    order.clear(); 
    is_back.clear();
  }

  void init() {
    depth.resize(n, 0);
    parent.resize(n, -1);
    root.resize(n, -1);
    sz.resize(n, 1);
    edge.resize(n, -1);
    depth.resize(n, 0);
    dist.resize(n, T{});
    back.resize(n, 0);
    child.resize(n, 0);
    is_back.resize((int) edges.size(), true);
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
      if (parent[nxt] == -1 && root[v] != nxt) {
        is_back[id] = false;
        depth[nxt] = depth[v] + 1;
        parent[nxt] = v;
        root[nxt] = root[v];
        edge[nxt] = id;
        dist[nxt] = dist[v] + e.w;
        Dfs(nxt);
        ++child[v];
        sz[v] += sz[nxt];
        back[v] += back[nxt];
      } else if (depth[nxt] < depth[v]) {
        ++back[v];
      } else {
        --back[v];      
      }
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

  dfs_tree(int _n) : undigraph<T>(_n) { }

  dfs_tree(const undigraph<T> _g) : undigraph<T>(_g) { }

};

template<typename T> vector<bool> bridges(dfs_tree<T> d) {
  if (d.depth.empty()) {
    d.dfs_all();
  }
  vector<bool> is((int) d.edges.size());
  for (int i = 0; i < d.n; ++i) {
    if (d.parent[i] == -1) {
      continue;
    }
    if (d.back[i] == 0) {
      is[d.edge[i]] = true;
    }
  }
  return is;
}



int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = (int) 1e5;
  int m = (int) 3e5;
  undigraph<int> g(n);
  while (m--) {
    g.add(rng() % n, rng() % n);    
  }
  dfs_tree d(g);
  d.dfs_all();
}
