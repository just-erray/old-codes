// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct SegTree {
  struct node {
    int mx = 0, mn = INT_MAX
    void set(int x) {
      mx = mn = x;
    }

    void modify(int x) {
      mx += x;
      mn += x;
    }
  };
  int n;
  vector<node> tree;
  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }  

  void modify(int ind, int x) {
    ind += n;
    tree[ind].modify(x);
    while (ind > 0) {
      ind >>= 1;
      tree[ind] = unite(tree[ind << 1], tree[(ind << 1) | 1]);
    }
  }

  node get(int l, int r) {
    ++r;
    r += n;
    l += n;

    while (l < r) {
      if (l & 1) {
        
      }
    }
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}