// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 template<typename A, typename B> string to_string(pair<A, B> p);
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t);
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t);

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(char c) {
  return string("'") + c + "'";
}

string to_string(const char* c) {
  return to_string(string(c));
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

template<size_t T> string to_string(bitset<T> bs) {
  return bs.to_string();
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < int(v.size()); ++i) {
    if (i > 0) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& e : v) {
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(e);
  }
  res += "}";
  return res;
}

template<typename A, typename B> string to_string(pair<A, B> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + '}';
}
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ", " + to_string(get<3>(t)) + '}';   
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << "  " << to_string(H);
  debug_out(T...);
}

#ifdef DEBUG 
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) void(37)
#endif

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
  SegTree st;
  vector<int> d;
  vector<int> size;
  vector<int> par;
  vector<int> ind;
  vector<int> root;
  int t = 0;
  void dfs(int v) {
    size[v] = 1;
    for (int i = 0; i < int(g[v].size()); ++i) {
      int u = g[v][i];
      if (u == par[v]) {
        continue;
      }
      d[u] = d[v] + 1;
      par[u] = v;
      dfs(u);
      size[v] += size[u];
      if (g[v][0] == par[v] || size[g[v][0]] < size[u]) {
        swap(g[v][i], g[v][0]);
      }
    }
  }

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
    par.resize(n, -1);
    ind.resize(n, -1);
    root.resize(n, 0);
    st = SegTree(n);
    dfs(0);
    index(0);
    debug(ind);
    debug(root);
    debug(par);
  }

  template<class T> void path(int v, int u, T op) {
    debug(v, u);
    while (root[v] != root[u]) {
      if (d[v] < d[u]) {
        swap(v, u);
      }  
      op(ind[root[v]], ind[v]);
      v = par[root[v]];
    }
    if (d[v] < d[u]) {
      swap(v, u);
    }  
    if (v != u) {
      op(ind[u] + 1, ind[v]);
    }
  }

  void modify(int v, int x) {
    path(v, par[v], [&](int l, int r) {
      assert(l == r);
      st.modify(l, x);
    });
  }

  int get(int v, int u) {
    int res = 0;
    path(v, u, [&](int l, int r) {
      res = max(res, st.get(l, r));
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
    HLD hld(n, hld_g);
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
