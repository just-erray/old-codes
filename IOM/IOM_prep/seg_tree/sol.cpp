// author: erray
#include<bits/stdc++.h>
 
using namespace std;

struct SegTree {
  struct node {
    int mx = 0, tag = 0;
    
    void modify(int x) {
      mx = max(mx, x);
      tag = max(tag, x);
    }
  };
  node emp;
  int n;
  vector<node> tree;

  node unite(const node& x, const node& y) {
    node res;
    res.mx = max(x.mx, y.mx);
    return res;
  }

  void push(int v, int l, int r) {
    if (l == r) {
      return;
    }
    int mid = (l + r) >> 1;
    int rv = l + ((mid - l) << 1);
 
    if (tree[v].tag != emp.tag) {
      tree[v + 1].modify(tree[v].tag);
      tree[rv].modify(tree[v].tag);
    }
    tree[v].tag = emp.tag;
  }

  void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]);
  }


  node get(int v, int l, int r, const int& ll, const int& rr) {
    if (l >= ll && rr >= r) {
      return tree[v];
    }

    int mid = (l + r) >> 1;
    int rv = v + ((mid - l) << 1);
    push(v, l, r);

    if (mid >= ll) {
      if (mid < rr) {
        return unite(get(v + 1, l, mid, ll, rr), get(rv, mid + 1, r, ll, rr));
      }    
      return get(v + 1, l, mid, ll, rr);
    } else {
      return get(rv, mid + 1, r, ll, rr);
    }
  }

  void modify(int v, int l, int r, const int& ll, const int& rr, const int& x) {
    if (l >= ll && rr >= r) {
      tree[v].modify(x);
      return;
    }   
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l) << 1);
    push(v, l, r);

    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, x);
    }

    if (mid < rr) {
      modify(rv, mid + 1, r, ll, rr, x);  
    }
    pull(v, rv);
  }

  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }

  node get(const int& ll, const int& rr) {
    assert(ll <= rr && ll >= 0 && rr < n);
    return get(0, 0, n - 1, ll, rr);
  }

  void modify(const int& ll, const int& rr, const int& x) {
    assert(ll <= rr && ll >= 0 && rr < n);
    modify(0, 0, n - 1, ll, rr, x);
  }

};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  SegTree st(n);
  for (int i = 0; i < n; ++i) {
    st.modify(i, i, a[i]);
  }

  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << st.get(l, r).mx << endl;
  }
}