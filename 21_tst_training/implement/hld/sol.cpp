// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 

struct SegTree {
  struct node {
    void modify(int l, int r, long long x) {
    }

    int get (int l, int r) {
      //..
      return l + r;
    }
  };

  node emp;
  
  node unite(const node& x, const node& y) {
    node res;

    return res;
  }
  
  inline void push(int v, int l, int r) {
  }
  
  /*----------------------------------Only up needs to change----------------------------------------*/

  inline void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]);
  }

  int n;
  vector<node> tree;

  template<typename T> void build(int v, int l, int r, const vector<T> vv) {     
    if (l == r) {
      tree[v].modify(l, r, vv[l]);
      return;
    }    
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    build(v + 1, l, mid, vv);
    build(rv, mid + 1, r, vv);
    pull(v, rv);
  }

  node get(int v, int l, int r, int ll, int rr) {
    if (l >= ll && rr >= r) {   
      return tree[v]; 
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    if (mid >= ll && mid < rr) {
      return unite(get(v + 1, l, mid, ll, rr), get(rv, mid + 1, r, ll, rr));          
    } 
    if (mid >= ll) {
      return get(v + 1, l, mid, ll, rr);    
    }
    return get(rv, mid + 1, r, ll, rr);
  }

  template<typename R, typename... T> R get(int v, int l, int r, int ll, int rr, function<R(const R&, const R&)> f, const T&... t) {
    if (l >= ll && rr >= r) {
      return tree[v].get(l, r, t...); 
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    if (mid >= ll && mid < rr) {
      return f(get(v + 1, l, mid, ll, rr, t...), get(rv, mid + 1, r, ll, rr, t...));          
    } 
    if (mid >= ll) {
      return get(v + 1, l, mid, ll, rr, t...);    
    }
    return get(rv, mid + 1, r, ll, rr, t...);
    
  }

  template<typename... T> void modify(int v, int l, int r, int ll, int rr, const T&... t) {
    if (l >= ll && rr >= r) {
      tree[v].modify(l, r, t...);
      return;      
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);
 
    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, t...);    
    }
    if (mid < rr) {
      modify(rv, mid + 1, r, ll, rr, t...);
    }
    pull(v, rv); 
  }

  template<typename... T> void set_modify(int v, int l, int r, int tar, const T&... t) {
    if (l == r) {
      tree[v] = emp;
      tree[v].modify(l, r, t...);
      return;      
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);
 
    if (mid >= tar) {
      set_modify(v + 1, l, mid, tar, t...);    
    }
    if (mid < tar) {
      set_modify(rv, mid + 1, r, tar, t...);
    }
    pull(v, rv); 
  }

  int find_first_exact(int v, int l, int r, const function<bool(const node&)> f) {
    if (!f(tree[v])) return -1;
    if (l == r) {
      return l;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    int res = -1;
    if (f(tree[v + 1])) {
      res = find_first_exact(v + 1, l, mid, f);
    } else {
      res = find_first_exact(rv, mid + 1, r, f);
    }
    assert(res != -1);
    return res;
  }

  int find_last_exact(int v, int l, int r, const function<bool(const node&)> f) {
    if (!f(tree[v])) return -1;
    if (l == r) {
      return l;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    int res = -1;
    if (f(tree[rv])) {
      res = find_last_exact(rv, mid + 1, r, f);
    } else {
      res = find_last_exact(v + 1, l, mid, f);
    }
    assert(res != -1);
    return res;
  }

  int find_first(int v, int l, int r, int ll, int rr, const function<bool(const node&)> f) {
    if (l >= ll && rr >= r) {
      return find_first_exact(v, l, r, f);
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    int res = -1;
    if (mid >= ll) {
      res = find_first(v + 1, l, mid, ll, rr, f);
    }
    if (res == -1 && mid < rr) {
      res = find_first(rv, mid + 1, r, ll, rr, f);
    }
    return res;
  }

  int find_last(int v, int l, int r, int ll, int rr, const function<bool(const node&)> f) {
    if (l > rr || r < ll) {
      return -1;
    }
    if (l >= ll && rr >= r) {
      return find_last_exact(v, l, r, f);
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    int res = -1;
    if (mid < rr) {
      res = find_last(rv, mid + 1, r, ll, rr, f);
    }
    if (res == -1 && mid >= ll) {
      res = find_last(v + 1, l, mid, ll, rr, f);
    }
    return res;
  }

  /*==========================================================================*/

  SegTree() { }

  SegTree(int _n) : n(_n) {
    assert(n > 0);
    tree.resize(n * 2 - 1);
  }

  template<typename T> SegTree(vector<T> v) : n((int) v.size()) {
    tree.resize(n * 2 - 1);
    build(0, 0, n - 1, v);        
  }

  node get(int ind) {
    assert(ind >= 0 && ind < n);
    return get(0, 0, n - 1, ind, ind);
  }
  
  node get(int l, int r) {  
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);  
    return get(0, 0, n - 1, l, r);
  }

  template<typename R, typename... T> R get(int l, int r, function<R(const R&, const R&)> f, T... t) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);  
    return get<R>(0, 0, n - 1, l, r, f, t...);
  }

  template<typename... T> void modify(int l, int r, T... t) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);
    modify(0, 0, n - 1, l, r, t...);    
  }

  template<typename... T> void set_modify(int ind, T... t) {
    assert(ind >= 0 && ind < n);
    set_modify(0, 0, n - 1, ind, t...);    
  }
  
  int find_first(int l, int r, const function<bool(const node&)> f) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);  
    return find_first(0, 0, n - 1, l, r, f);    
  }

  int find_last(int l, int r, const function<bool(const node&)> f) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);  
    return find_last(0, 0, n - 1, l, r, f);    
  }
  
  int find_first(const function<bool(const node&)> f) {
    return find_first(0, 0, n - 1, 0, n - 1, f);    
  }

  int find_last(const function<bool(const node&)> f) {
    return find_last(0, 0, n - 1, 0, n - 1, f);    
  }  
};


struct HLD {
  vector<int> d;
  vector<int> size;
  vector<int> root;
  vector<int> ind;     
  vector<int> par;
  vector<vector<int>> g;
  SegTree st;
  int n;

  void dfs(int v) {
    for (int i = 0; i < int(g[v].size()); ++i) {
      if (g[v][i] == par[v]) {
        continue;
      }
      int u = g[v][i];
      d[u] = d[v] + 1;
      par[u] = v;
      dfs(u);
      size[v] += size[u];
      if (g[v][0] == par[v] || size[g[v][0]] < size[g[v][i]]) {
        swap(g[v][0], g[v][i]);
      }
    }
  }

  int t = 0;
  void index(int v) {
    ind[v] = t++;
    bool first = true;
    for (auto u : g[v]) {
      if (u == par[v]) {
        continue;
      }
      if (first) {
        root[u] = root[v];
        first = false;
      } else {
        root[u] = u;
      }
      index(u);
    }
  }

  HLD(int _n, vector<vector<int>> _g) : n(_n), g(_g) {
    d.resize(n, 0);
    size.resize(n, 1);
    root.resize(n, 0);
    ind.resize(n, 0);
    par.resize(n, -1);
    st = SegTree(n);
  }

  template<class T> void path(int v, int u, T op) {
    while (root[v] != root[u]) {
      if (d[root[u]] > d[root[v]]) {
        swap(v, u);
      }
      op(ind[root[v]], ind[v]);
      v = par[root[v]];
    }
    if (d[u] > d[v]) {
      swap(v, u);
    }
    op(ind[u], ind[v]);
  }
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}