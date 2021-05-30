// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct bit {
  vector<int> tree;
  int n;

  int lb(int x) {
    return x & -x;
  }

  bit(int _n) : n(_n) {
    tree.resize(n + 1);
  }

  void modify(int x, int y) {
    ++x;
    while (x <= n) {
      tree[x] += y;
      x += lb(x);
    }
  }

  int get(int x) {
    ++x;
    int res = 0;
    while (x > 0) {
      res += tree[x];
      x -= lb(x);
    }
    return res;
  }

  int bs(int x) {
    int big = 1;
    while (big < n) {
      big >>= 1;
    }
    int res = 0;
    while (res <= n && big > 0) {
      if (res + big <= n) {
        if (tree[res + big] <= x) {
          res += big;
          x -= tree[res];
        }
      }  
      big >>= 1;
    }
    return res;
  }
};

 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int n, t;
  cin >> n >> t;
  vector<pair<int, int>> a(t);
  bit b(n);
  for (int i = 0; i < t; ++i) {
    cin >> a[i].first;    
    a[i].first = b.bs(a[i].first);
    b.modify(a[i].first, -1);
    a[i].second = i;  
  }
  sort(a.begin(), a.end());

  auto Ask = [&](int l, int r) {
    assert(l <= r && r < n && l >= 0);
    cout << "? " << l + 1 << ' ' << r + 1 << endl;
    int res;
    cin >> res;
    return res;
  };


  vector<int> ans(t);
  function<void(int, int, int, int)> Solve = [&](int l, int r, int ll, int rr) {
    if (ll > rr) {
      return;
    }

    int dmid = (ll + rr) >> 1;
    int low = l, high = r;
    while (low < high) {
      int mid = (low + high) >> 1;
      if (Ask(0, mid) > mid + 1 - a[dmid].first) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }

    ans[a[dmid].second] = low;
    Solve(l, low - 1, ll, dmid - 1);
    Solve(low + 1, r, dmid + 1, rr);
  };

  for (int i = 0; i < t; ++i) {
    cout << "! " << ans[i] + 1 << endl;
  }
}