// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
struct SegTree {
  struct node {
    int mx = 0;
    int tag = 0;
    void modify(int x) {
      mx += x;
      tag += x;
    }
  };

  node unite(const node& x, const node& y) {
    node res;
    res.mx = max(x.mx, y.mx);
    return res;
  }
  
  vector<node> tree;
  int n;

  void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]);  
  }

  void push(int v, int rv) {
    if (tree[v].tag != 0) {
      tree[v + 1].modify(tree[v].tag);
      tree[rv].modify(tree[rv].tag);
    }
  }

  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }

  void modify(int v, int l, int r, int ll, int rr, int x) {
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
      modify(rv, mid + 1, r, ll, rr, x);
    }
    pull(v, rv);
  }

  node get(int v, int l, int r, int ll, int rr) {
    if (l >= ll && rr >= r) {
      return tree[v];
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (mid >= ll && mid < rr) {
      return unite(get(v + 1, l, mid, ll, rr), get(rv, mid + 1, r, ll, rr));
    } else if (mid >= ll) {
      return get(v + 1, l, mid, ll, rr);
    } else {
      return get(rv, mid + 1, r, ll, rr);
    }
  }

};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
}