// author: erray
#include<bits/stdc++.h>
 
using namespace std;

struct SegTree {
  int n;
  vector<bool> tree;
  void modify(int v, int l, int r, int t) {
    if (l == r) {
      tree[v] = tree[v] ^ true;
      return;
    } 
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (mid >= t) {
      modify(v + 1, l, mid, t);
    } else {
      modify(rv, mid + 1, r, t);
    }
    tree[v] = tree[v + 1] && tree[rv];
  }

  int get(int v, int l, int r) {
    if (l == r) {
      return l;
    }
    
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (tree[v + 1]) {
      return get(rv, mid + 1, r);
    } else {
      return get(v + 1, l, mid);
    }
  }

  void modify(int t) {
    modify(0, 0, n - 1, t);
  }

  int get() {
    return get(0, 0, n - 1);
  }

  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> ct(n);
  SegTree st(n + 1);
  auto add = [&](int x, int y) {
    ct[x] += y;
    if ((ct[x] == 0 && y == -1) || (ct[x] == 1 && y == 1)) {
      st.modify(x);
    } 
  };

  for (int i = 0; i < m; ++i) {
    add(a[i], 1);  
  }
  
  int ans = st.get();
  for (int i = 0; i < n - m; ++i) {
    add(a[i], -1);
    add(a[i + m], +1);
    ans = min(ans, st.get());
  }
  cout << ans << '\n';
}