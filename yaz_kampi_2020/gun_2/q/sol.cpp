// author: erray
#include<bits/stdc++.h>
 
using namespace std;

class SegTree {
  public:
  struct node {
    //variables default values should be uneffective
    long long left, right, mid, sum, mx;
    void modify(int l, int r, long long x) {
      left = right = mid = max(0LL, x);  
      sum = x;
      mx = x;
    }

    int get (int l, int r) {
      
      return l + r;
    }
  };

  node emp;

  node unite(const node& x, const node& y) {
    node res;
    res.left = max(x.left, x.sum + y.left);
    res.right = max(y.right, y.sum + x.right);
    res.sum = y.sum + x.sum;
    res.mid = max({x.right + y.left, y.mid, x.mid});
    res.mx = max(x.mx, y.mx);
    return res;
  }

  inline void push(int v, int l, int r) {
    if (l == r) return;
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

    /*==========================================================================*/


  SegTree(int _n) : n(_n) {
    assert(n > 0);
    tree.resize(n * 2 - 1);
  }

  node get(int l, int r) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);
    return get(0, 0, n - 1, l, r);
  }

  template<typename... T> void modify(int l, int r, T... t) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);
    modify(0, 0, n - 1, l, r, t...);
  }

};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  SegTree st(n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    st.modify(i, i, x);
  }
  int q;
  cin >> q;
  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 0) {
      st.modify(x - 1, x - 1, (long long) y);
    } else {
      --x, --y;
      auto res = st.get(x, y);
      if (res.mx < 0) {
        cout << res.mx << '\n';
        continue;
      }
      cout << res.mid << '\n';
    }
  }
}