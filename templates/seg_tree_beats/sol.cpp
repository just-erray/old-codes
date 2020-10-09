// author: erray
#include<bits/stdc++.h>
 
using namespace std;

class segTree {
  public:
  
  struct node {
    long long sum = 0;
    int lazy = INT_MAX, mx = 0, mx2 = 0, ct = 1;

    void modify(int l, int r, int x) {
      
    }
  };

  node unite(const node& x, const node& y) {
    node res;
    res.sum = x.sum + y.sum;
    res.mx = max(x.mx, y.mx);
    if (x.mx == y.mx) {
      res.mx2 = max(y.mx2, x.mx2);
    } else {
      res.mx2 = max({min(y.mx, x.mx), y.mx2, x.mx2});
    }
    res.ct = (x.mx == res.mx ? x.ct : 0) + (y.mx == res.mx ? y.ct : 0);
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);      
  cin.tie(0);
  
}