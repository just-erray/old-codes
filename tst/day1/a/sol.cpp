//author: erray
#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> string to_string(pair<A, B> p);
string to_string(string s) {
  return '"' + s + '"';
}

string to_string(const char* c) {
  return to_string(string(c));
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < int(v.size()); ++i) {
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(const T& v) {
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
  struct node {
    long long sum = 0;
    long long tag = 0;
    void modify(int l, int r, long long x) {
      sum += (r - l + 1) * x;
      tag += x;
    }
  };

  node unite(const node& x, const node& y) {
    node res;
    res.sum = x.sum + y.sum;
    return res;
  }

  void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]); 
  }

  void push(int v, int l, int r) {
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (tree[v].tag != 0) {
      tree[v + 1].modify(l, mid, tree[v].tag);
      tree[rv].modify(mid + 1, r, tree[v].tag);
      tree[v].tag = 0;
    }
  }

  int n;
  vector<node> tree;
  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }  

  void modify(int v, int l, int r, int ll, int rr, int x) {
    if (l >= ll && rr >= r) {
      tree[v].modify(l, r, x);
      return;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);
    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, x);
    }
    if (mid < rr) {
      modify(rv, mid + 1, r, ll, rr, x);
    }
    pull(v, rv);
  }

  long long get(int v, int l, int r, int ll) {
    if (l >= ll) {
      return tree[v].sum;
    } 
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);
    long long res = 0;
    if (mid >= ll) {
      res += get(v + 1, l, mid, ll);
    }
    res += get(rv, mid + 1, r, ll);
    return res;
  }

  void modify(int ll, int rr) {
    assert(ll >= 0 && rr < n && ll <= rr);
    modify(0, 0, n - 1, ll, rr, 1);
  }

  long long get(int ll) {
    assert(ll >= 0 && ll < n);
    return get(0, 0, n - 1, ll);
  }
};

struct SparseTable {
  vector<vector<int>> table;
  int n;
  SparseTable(vector<int> a) {
    n = int(a.size());
    int lg = 32 - __builtin_clz(n);
    table.resize(lg);
    table[0] = a;
    for (int j = 1; j < lg; ++j) {
      int size = n + 1 - (1 << j);
      table[j].resize(size);
      for (int i = 0; i < size; ++i) {
        table[j][i] = max(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  int get(int l, int r) {
    assert(l >= 0 && r < n && l <= r);
    int lg = 31 - __builtin_clz(r - l + 1);
    return max(table[lg][l], table[lg][r + 1 - (1 << lg)]);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vector<long long> pref(n + 1);
  for (int i = 0; i < n; ++i) {
    pref[i + 1] = pref[i] + a[i];
  }

  auto Sum = [&](int l, int r) {
    return pref[r + 1] - pref[l];
  };

  vector<vector<pair<int, int>>> qs(n);
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    --l, --r;
    qs[r].emplace_back(l, i);
  }

  debug("hi");
  SparseTable mx(a);
  auto Next = [&](int i, long long big) {
    if (mx.get(0, i) < big) {
      return -1;
    }

    int low = 0, high = i;
    while (low < high) {
      int mid = ((low + high) >> 1) + 1;
      if (mx.get(mid, i) >= big) {
        low = mid;
      } else {
        high = mid - 1;
      }
    }
    return low;
  };

  vector<long long> ans(q);
  SegTree sum(n);
  for (int i = 0; i < n; ++i) {
    int cur = i;
    while (cur != -1) {
      if (Sum(cur + 1, i) < a[cur]) {
        int low = 0, high = cur;
        while (low < high) {
          int mid = (low + high) >> 1;
          if (Sum(mid, i) >= a[cur] * 2) {
            low = mid + 1;
          } else {
            high = mid;
          }
        }
        sum.modify(low, cur);
      }
      cur = Next(cur, Sum(cur, i) + 1);   
    }

    for (auto e : qs[i]) {
      int l, id;
      tie(l, id) = e;
      ans[id] = sum.get(l);
    }
  }

  for (int i = 0; i < q; ++i) {
    cout << ans[i] << '\n';
  }
}                                                                                                                                     