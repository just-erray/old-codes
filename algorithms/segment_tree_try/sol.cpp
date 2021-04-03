// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct SegTree {
  struct node {
    long long mx = 0, tag = 0;
    void modify(long long x) {
      mx += x;
      tag += x;
    }
  };

  int n;
  vector<node> tree;

  void push(int v, int rv) {
    if (tree[v].tag != 0) {
      tree[v + 1].modify(tree[v].tag);
      tree[rv].modify(tree[v].tag);
    }
    tree[v].tag = 0;
  }

  node unite(const node x, const node y) {
    node res;
    res.mx = max(x.mx, y.mx);
    return res;
  }

  void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]);
  }

  SegTree(int _n) : n(_n), tree((n << 1) - 1) {}

  void modify(int v, int l, int r, const int& ll, const int& rr, const int& c) {
    if (l >= ll && rr >= r) {
      tree[v].modify(c);
      return;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, c);
    }
    if (mid < rr) {
      modify(rv, mid + 1, r, ll, rr, c);
    }
  }

  node get(int v, int l, int r, const int& ll, const int& rr) {
    if (l >= ll && rr >= r) {
      return tree[v];
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    node res;
    if (mid >= ll) {
      if (mid < rr) {
        return unite(get(v + 1, l, mid, ll, rr), get(rv, mid + 1, r, ll, rr));
      } else {
        return get(v + 1, l, mid, ll, rr);
      }
    } else {
      return get(rv, mid + 1, r, ll, rr);
    } 
    assert(false);
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
   
}