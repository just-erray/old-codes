// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct SegTree {
  struct node {
    long long mx = 0;
    long long tag = 0;
    void modify(long long x) {
      mx += x;
      tag += x;
    }
  };

  
  node operator+(node x, node y) {
    node res;
    res.mx = max(x.mx, y.mx);
    return res;
  }

  void push(int v, int rv) {
    if (tree[v].tag != 0) {
      tree[v + 1].modify(tree[v].tag);
      tree[rv].modify(tree[v].tag);
      tree[v].tag = 0;
    }
  }
  
  void pull(int v, int rv) {
    tree[v] = tree[v + 1] + tree[rv];
  }


  int n;
  vector<node> tree;
  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }

  SegTree() { }

  void modify(int v, int l, int r, int ll, int rr, long long x) {
    if (l >= ll && rr >= r) {
      tree[v].modify(x);
      return;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, rv);
    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, x);
    } 
    if (mid < rr) {
      modify(rv, mid + 1, rr, ll, rr, x);
    }
    pull(v, rv);
  }

  node get(int v, int l, int r, int ll, int rr) {
    if (l >= ll && rr >= r) {
      return tree[v];
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (mid >= ll) {
      if (mid < rr) {
        return get(v + 1, l, mid, ll, rr) + get(rv, mid + 1, rr, ll, rr);
      } else {
        return get(v + 1, l, mid, ll, rr);
      }
    } else {
      return get(rv, l, mid, ll, rr);
    }
  }

  void modify(int ll, int rr, long long x) {
    assert(ll >= 0 && ll >= rr && rr < n);
    modify(0, 0, n - 1, ll, rr, x);
  }

  node get(int ll, int rr) {
    assert(ll >= 0 && ll >= rr && rr < n);  
    return get(0, 0, n - 1, ll, rr);
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
  }
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
  }

  vector<int> p(k);
  for (int i = 0; i < k; ++i) {
    cin >> p[i];
  }
  vector<SegTree> dp(n + 1);
  dp[0] = SegTree(1); 
  for (int i = 1; i <= n; ++i) {
    
  }
}