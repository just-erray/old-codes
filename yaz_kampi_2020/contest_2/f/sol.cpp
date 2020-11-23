// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T, typename F = function<T(const T&, const T&)>> class Bit {
  public:
  vector<T> tree;
  F cal;
  int sz;
  int lb(int x) { return x & -x; }
  void modify(int ind, T val) {
    ++ind;
    while (ind < sz) {
      tree[ind] = cal(tree[ind], val);
      ind += lb(ind);
    }
  }
  Bit(vector<T> v, T uneff, F _cal) : cal(_cal) {
    sz = (int) v.size() + 1;
    tree.resize(sz, uneff);
    for (int i = 0; i < (int) v.size(); ++i) modify(i, v[i]);
  }
  T get(int ind) {
    ++ind;
    T res = tree[0];
    while (ind) {
      res = cal(res, tree[ind]);
      ind -= lb(ind);
    }
    return res;
  }
  void clear() {
    fill(tree.begin(), tree.end(), tree[0]);
  }
};

class SegTree {
  public:
  struct node {
    //variables default values should be uneffective
    int val = (int) 1e6, lazy = (int) 1e6;
    void modify(int l, int r, int x) {
      val = min(val, x);     
      lazy = min(lazy, x);
    }

    int get (int l, int r) {
      //..
      return l + r;
    }
  };

  node emp;

  node unite(const node& x, const node& y) {
    node res;
    res.val = min(x.val, y.val);
    return res;
  }

  inline void push(int v, int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (tree[v].lazy != emp.lazy) {
      tree[rv].modify(mid + 1, r, tree[v].lazy);
      tree[v + 1].modify(l, mid, tree[v].lazy);
    }
    tree[v].lazy = emp.lazy;
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
    set_modify(0, 0, n - 1, ind, ind, t...);
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
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int cs = 10;
  while (cs--) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
  }
  Bit<int> fenw(vector<int>(n), 0, [](int x, int y) {
    return max(x, y);
  });
  vector<int> dp(n, 1);
  for (int i = 0; i < n; ++i) {
    if (a[i] > 0) {
      dp[i] = fenw.get(a[i] - 1) + 1;
    }
    fenw.modify(a[i], dp[i]);
  }
  SegTree st(n);
  int mx = fenw.get(n - 1);
  st.modify(0, n - 1, mx);
  vector<int> ans;

  for (int i = n - 1; i >= 0; --i) {
    if (dp[i] >= st.get(a[i]).val) {
      ans.push_back(a[i]);
      st.modify(0, a[i], dp[i] - 1); 
    }      
  }
  sort(ans.begin(), ans.end());
  cout << (int) ans.size() << '\n';
  for (auto el : ans) {
    cout << el + 1 << ' ';
  }
  cout << '\n';
  }
}