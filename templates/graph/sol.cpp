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

  virtual void add(int v, int u, T w = 1) = 0; 
};

template<typename T> class digraph : public graph<T> {
  public:    
  using graph<T>::n;  
  using graph<T>::g;
  using graph<T>::edges;

  digraph(int _n) : graph<T>(_n) { }

  void add(int v, int u, T w = 1) {
    assert(v >= 0 && u >= 0 && v < n && u < n);
    int id = (int) edges.size();
    g[v].push_back(id);
    g[u].push_back(id); //for reverse edges
    edges.push_back({v, u, w});
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

  void add(int v, int u, T w = 1) {
    assert(v >= 0 && u >= 0 && v < n && u < n);
    int id = (int) edges.size();
    g[v].push_back(id);
    g[u].push_back(id);
    edges.push_back({v, u, w});
  }
};

template<typename T> class forest : public graph<T> {
  public:    
  using graph<T>::n;  
  using graph<T>::g;
  using graph<T>::edges;
  
  forest(int _n) : graph<T>(_n) { }

  void add(int v, int u, T w = 1) {
    assert(v >= 0 && u >= 0 && v < n && u < n);
    int id = (int) edges.size();
    assert(id < n - 1);
    g[v].push_back(id);
    g[u].push_back(id);
    edges.push_back({v, u, w});
  }
};

template<typename T> dfs_forest : public forest<T> {
  public:
  using graph<T>::n;  
  using graph<T>::g;
  using graph<T>::edges;

  vector<int> depth, parent, source,   
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  digraph<int> g(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    g.add(x, y);
  }
  
}
