// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct SegTree {
  struct node {
    //variables default values should be uneffective     
    int mx = 0;
    void modify(int l, int r, int x) {
      mx = x;
    }

    int get (int l, int r) {
      //..
      return l + r;
    }
  };

  node emp;
  
  node unite(const node& x, const node& y) {
    node res;
    res.mx = max(x.mx, y.mx);
    return res;
  }
  
  inline void push(int v, int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (tree[v].tag != emp.tag) {
      tree[rv].modify(mid + 1, r, tree[v].tag); 
      tree[v + 1].modify(l, mid, tree[v].tag); 
    }
    tree[v].tag = emp.tag;
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

struct lca {
  int n, lg;
  vector<vector<int>> par;
  vector<int> d;
  lca(vector<int> parent, vector<int> _d) : d(_d) {
    n = int(parent.size());
    lg = __lg(n) + 2;
    par.resize(lg);
    par[0] = parent;
    for (int j = 1; j < lg; ++j) {
      for (int i = 0; i < n; ++i) {
        par[j][i] = par[j - 1][par[j - 1][i - 1]];
      }
    }
  }

  int get(int x, int y) {
    if (d[x] > d[y]) {
      swap(x, y);
    }  
    int go = d[y] - d[x];
    int b = 0;
    while (go > 0) {
      if (go & 1) {
        y = par[b][y];
      }
      go >>= 1;
      ++b;
    }
    if (x == y) {
      return x;
    }
    for (int j = lg - 1; j >= 0; --j) {
      if (par[j][x] != par[j][y]) {
        x = par[j][x];
        y = par[j][y];
      }
    }
    assert(par[0][x] == par[0][y]);
    return par[0][x];
  }
};

struct hld {
  int n;
  int lst_id = 0;
  vector<vector<int>> g;
  vector<array<int, 3>> es;
  vector<int> d;
  vector<int> par;
  vector<int> edge_id;
  vector<int> node_id;
  vector<int> size;
  vector<bool> big;
  
  void dfs_pre(int v) {
    for (auto id : g[v]) {
      if (es[id][0] == par[v]) {
        continue;
      }
      if (es[id][0] != v) {
        swap(es[id][0], es[id][1]);
      }
      int u = es[id][1];
      par[u] = v;
      d[u] = d[v] + 1;
      dfs_pre(u);
      size[v] += size[u];
    }
    int p = 0;
    while (p < int(g[v].size()) && es[g[v][p]][0] == v) {
      ++p;
    }
    if (p < int(g[v].size())) {
      g[v].erase(g[v].begin() + p);
    }
  }



  hld(vector<vector<int>> _g, vector<array<int, 3>> _es) : g(_g), es(_es), n(int(g.size()) + 1) {
    d.resize(n, 0);
    par.resize(n, -1);
    size.resize(n, 1);
    dfs_pre(0);
    big.resize(n, false);
    edge_id.resize(n - 1, 0);
    node_id.resize(n, 0);
  } 
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  while (T--) {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    vector<array<int, 3>> es(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      int x, y, w;
      cin >> x >> y >> w;
      --x, --y;
      es[i] = {x, y, w};
      g[x].push_back(i);
      g[y].push_back(i);
    }
    hld h(es, g);
    while (true) {
      string q;
      cin >> q;
      if (q == "DONE")  {
        break;
      }

      int x, y;
      cin >> x >> y;
      if (q == "CHANGE") {
        h.modify(x - 1, y);
      } else if (q == "QUERY") {
        cout << h.get(x - 1, y - 1) << '\n';
      } else {
        assert(false);
      }
    }
  }
}