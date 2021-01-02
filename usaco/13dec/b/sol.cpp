// author: erray
#include<bits/stdc++.h>
 
using namespace std;

struct SegTree {
  struct node {
    long long all = 0, l = 0, r = 0, lr = 0;
    void modify(int x) {
      all = x;
    }
  };
  int n;
  vector<node> tree;

  node unite(const node& x, const node& y) {
    node res;
    res.all = max(x.r + y.all, x.all + y.l);
    res.l = max(x.l + y.l, x.lr + y.all);
    res.r = max(x.r + y.r, x.all + y.lr);
    res.lr = max(x.lr + y.r, x.l + y.lr);
    return res;
  }

  void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]);
  }

  void modify(int v, int l, int r, int tar, int w) {
    if (l == r) {
      tree[v].modify(w); 
      return;
    }
    
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    (mid >= tar ? modify(v + 1, l, mid, tar, w) : modify(rv, mid + 1, r, tar, w));
    pull(v, rv);
  }

  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }

  void modify(int tar, int w) {
    modify(0, 0, n - 1, tar, w);  
  }

  long long ans() {
    return tree[0].all;
  }
    
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "optmilk";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, d;
  cin >> n >> d;
  SegTree st(n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    st.modify(i, x);
  }

  long long ans = 0;
  for (int i = 0; i < d; ++i) {
    int x, y;
    cin >> x >> y;
    --x;
    st.modify(x, y);
    ans += st.ans();
  }

  cout << ans << '\n';
}