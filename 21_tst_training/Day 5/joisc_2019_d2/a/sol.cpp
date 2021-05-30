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

struct SegTreeIt {
  int n;
  vector<int> mx;
  void modify(int p, int x) {
    for (mx[p += n] = x; p > 0; p >>= 1) {
      mx[p >> 1] = max(mx[p], mx[p ^ 1]);
    }
  }

  int get(int l, int r) {
    int res = -1;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res = max(res, mx[l++]);
      }
      if (r & 1) {
        res = max(res, mx[--r]);
      }
    } 
    return res;
  }

  SegTreeIt(int _n) : n(_n) {
    mx.resize((n << 1), -1);
  }
};

struct SegTree {
  struct node {
    int mx = INT_MIN, tag_mx = INT_MIN;
    int mn = INT_MAX, tag_mn = INT_MAX;
    int mx_v = INT_MIN;
    int mn_v = INT_MAX;
    int res = -1;
    int active = 0;
    bool tagged = false;
    void modify(int x, int type) {
      /*
        0 = add
        -1 = erase
        1 = set res
        2 = range update
      */
      if (type == 0) {
        mx_v = mn_v = x;
        mx = x - 1;
        mn = x + 1;
        active = 1;
      } else if (type == -1) {
        mx_v = INT_MIN;
        mn_v = INT_MAX;
        res = -1;
        active = 0;
      } else if (type ==  2) {                
        debug(x);
        tagged = true;
        tag_mx = max(x, tag_mx);
        tag_mn = min(x, tag_mn);
        mx = max(x, mx);
        mn = min(x, mn);
        debug(mn, mx);
        debug(mn_v, mx_v);
        if (active) {
          res = max({res, mx - mn_v, mx_v - mn});
        }
      } else {
        assert(false);
      }
    }
  };

  int n;
  vector<node> tree;

  node unite(const node& x, const node& y) {
    node res;
    res.mx_v = max(x.mx_v, y.mx_v);
    res.mn_v = min(res.mn_v, y.mn_v);
    res.res = max(x.res, y.res);
    res.active = x.active + y.active;
    return res;
  }

  void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]);
  }

  void push(int v, int rv) {
    /*
    if (rv >= ((n << 1) - 1)) {
      return;
    }
    */
    if (tree[v].tagged) {
      tree[v + 1].modify(tree[v].tag_mx, 2);
      tree[v + 1].modify(tree[v].tag_mn, 2);
      tree[rv].modify(tree[v].tag_mx, 2);
      tree[rv].modify(tree[v].tag_mn, 2);
      tree[v].tag_mx = INT_MIN;
      tree[v].tag_mn = INT_MAX;
      tree[v].tagged = false;
    }
  }
  void modify(int v, int l, int r, const int& ll, const int& rr, const int& x, const int& type) {
    //debug(v, l, r, ll, rr);
    if (l >= ll && rr >= r) {
      debug("update", l, r, x, type);
      tree[v].modify(x, type);
      return;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);          
    push(v, rv);
    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, x, type);
    }
    if (mid < rr) {
      modify(rv, mid + 1, r, ll, rr, x, type);
    }
    pull(v, rv);
  }

  int get(int v, int l, int r, const int& ll, const int& rr) {
    if (l >= ll && rr >= r) {
      return tree[v].res;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, rv);
    int res = -1;
    if (mid >= ll) {
      res = max(res, get(v + 1, l, mid, ll, rr));
    }
    if (mid < rr) {
      res = max(res, get(rv, mid + 1, r, ll, rr));
    }
    return res;
  }

  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }

  void modify(int ll, int rr, int x, int type) {
    assert(ll >= 0 && ll <= rr && rr < n);
    modify(0, 0, n - 1, ll, rr, x, type);
  }

  void modify(int t, int x, int type) {
    assert(t >= 0 && t < n);
    modify(0, 0, n - 1, t, t, x, type);
  }

  int get(int ll, int rr) {
    assert(ll >= 0 && ll <= rr && rr < n);
    return get(0, 0, n - 1, ll, rr);    
  }

  void dbg(int v, int l, int r) {
    debug(l, r, tree[v].mn, tree[v].mx, tree[v].mn_v, tree[v].mx_v, tree[v].res);
    if (l == r) {
      return;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    dbg(v + 1, l, mid);
    dbg(rv, mid + 1, r); 
  }

  void dbg() {
    #ifdef DEBUG
    dbg(0, 0, n - 1);
    #endif
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> h(n), a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> h[i] >> a[i] >> b[i];
  }

  int q;
  cin >> q;
  vector<int> l(q), r(q);
  for (int i = 0; i < q; ++i) {
    cin >> l[i] >> r[i];
    --l[i], --r[i];
  }

  auto Solve = [&] {
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
      return r[x] < r[y];
    });  
    vector<vector<int>> start(n + 1);
    vector<vector<int>> end(n + 1);
    for (int i = 0; i < n; ++i) {
      int ll = i + a[i];
      int rr = i + b[i] + 1;
      ll = min(ll, n);
      rr = min(rr, n);
      start[ll].push_back(i);
      end[rr].push_back(i);
    }

    SegTree act(n);
    SegTreeIt pas(n);
    int p = 0;
    vector<int> res(q);
    for (auto i : ord) {
      debug(r[i]);
      while (r[i] >= p) {
        /*
          0 = add
          -1 = erase
          1 = set res
          2 = range update
        */
        debug(p);
        for (auto e : start[p]) {
          act.modify(e, h[e], 0); 
          debug(e, h[e], "set");
        }
        for (auto e : end[p]) {
          pas.modify(e, act.get(e, e));          
          debug(e, "remove and add");
          act.modify(e, -1, -1);
        }
        int left = max(0, p - b[p]);
        int right = p - a[p];
        if (right >= 0) {
          debug(left, right, h[p], "segment add"); 
          act.modify(left, right, h[p], 2);
        }
        ++p;
      }
      /*
      debug("active");
      act.dbg();
      debug("passive");
      pas.dbg();
      */
      res[i] = max(act.get(l[i], r[i]), pas.get(l[i], r[i]));
      debug("ans", res[i]);
    }
    return res;
  };

  vector<int> ans = Solve();
  for (int i = 0; i < q; ++i) {
    cout << ans[i] << '\n';  
  }
}