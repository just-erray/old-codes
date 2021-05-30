// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct SegTree {
  int n;
  vector<int> tree;
  SegTree() { } 
  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }

  int op(int x, int y) {
    return max(x, y);
  }
  
  void pull(int v, int rv) {
     tree[v] = op(tree[v + 1], tree[rv]);
  }

  int get(int v, int l, int r, int ll, int rr) {
    if (l >= ll && rr >= r) {
      return tree[v];
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (mid >= ll) {
      if (mid < rr) {
        return op(get(v + 1, l, mid, ll, rr), get(rv, mid + 1, r, ll, rr));
      } else {
        return get(v + 1, l, mid, ll, rr);
      }
    } else {
      return get(rv, mid + 1, r, ll, rr);
    }
  }

  void modify(int v, int l, int r, int p, int x) {
    if (l == r) {
      tree[v] = x;
      return;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (mid >= p) {
      modify(v + 1, l, mid, p, x);
    } else {
      modify(rv, mid + 1, r, p, x);
    }
    pull(v, rv);
  }
  void modify(int p, int x) {
    assert(p >= 0 && p < n);
    modify(0, 0, n - 1, p, x);
  }
  int get(int l, int r) {
    assert(l >= 0 && l <= r && r < n);
    return get(0, 0, n - 1, l, r);
  }
};

struct HLD {    
  int n;
  vector<vector<int>> g;
  vector<SegTree> sts;
  vector<int> size;
  vector<int> heavy;
  vector<int> d;
  vector<int> id;     
  vector<int> root;
  vector<int> ind;
  vector<int> st_size;
  vector<int> par;       
  bool edge = false;
  int tree = 0;
  void dfs(int v) {
    for (auto u : g[v]) {
      if (u == par[v]) {
        continue;
      }
      par[u] = v;
      d[u] = d[v] + 1;
      dfs(u);        
      size[v] += size[u];
      if (heavy[v] == -1 || size[u] > size[heavy[v]]) {
        heavy[v] = u;
      }
    }
  }   
  
  void index(int v) {
    for (auto u : g[v]) {
      if (u == par[v]) {
        continue;
      }
      if (heavy[v] == u) {
        id[u] = id[v]; 
        ind[u] = ind[v] + 1;
        st_size[id[v]]++;
      } else {
        id[u] = tree++;
        root.push_back(u);
        st_size.push_back(1);
        ind[u] = 0;
      }
      index(u);
    }  
  }

  HLD(int _n, vector<vector<int>> _g, bool _edge = false) : n(_n), g(_g), edge(_edge) {
    size.resize(n, 1);
    heavy.resize(n, -1);  
    d.resize(n, 0);
    par.resize(n, -1);
    dfs(0);
    id.resize(n, 0);
    ind.resize(n, 0);
    st_size.push_back(1);
    root.push_back(0);
    tree = 1;
    index(0);
    sts.resize(tree);
    for (int i = 0; i < tree; ++i) {
      sts[i] = SegTree(st_size[i]);
    }
  }

  
  template<typename T> void path(int u, int v, T op) {
    while (id[u] != id[v]) {
      if (d[u] > d[v]) {
        swap(u, v);
      }
      op(id[v], 0, ind[v]);
      v = par[root[id[v]]];   
    }
    if (d[u] > d[v]) {
      swap(u, v);
    }
    if (edge) {
      if (v != u) {
        op(id[v], ind[u] + 1, ind[v]);
      }
    } else {
      op(id[v], ind[u], ind[v]);
    }
  }

  void modify(int v, int x) {
    path(par[v], v, [&](int st, int l, int r) {
      assert(l == r);
      sts[st].modify(l, x);
    });
  }

  int get(int u, int v) {
    int res = 0;
    path(u, v, [&](int st, int l, int r) {
      res = max(res, sts[st].get(l, r));
    });
    return res;
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    vector<int> ver(n - 1);
    vector<int> w(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      int x, y, c;
      cin >> x >> y >> c;
      w[i] = c;
      --x, --y;
      g[x].emplace_back(y, i);
      g[y].emplace_back(x, i);
    }

    vector<vector<int>> hld_g(n);
    for (int i = 0; i < n; ++i) {
      for (auto e : g[i]) {
        hld_g[i].push_back(e.first);
      }
    }
    HLD hld(n, hld_g, true);
    function<void(int, int)> Dfs = [&](int v, int pr) {
      for (auto e : g[v]) {
        int u;
        int id;
        tie(u, id) = e;
        if (u == pr) {
          continue;
        }
        ver[id] = u;
        Dfs(u, v);
      }
    };
    Dfs(0, -1);    
    auto Modify = [&](int e, int x) {
      hld.modify(ver[e], x);
    };
    for (int i = 0; i < n - 1; ++i) {
      Modify(i, w[i]);
    }
    while (true) {
      string query;
      cin >> query;
      if (query == "DONE") {
        break;
      }
      if (query == "CHANGE") {
        int edge, new_c;
        cin >> edge >> new_c;
        --edge;
        Modify(edge, new_c);
      } else if (query == "QUERY") {
        int v, u;
        cin >> v >> u;
        --v, --u;
        cout << hld.get(v, u) << '\n';
      } else {
        assert(false);
      }
    }

  }
}