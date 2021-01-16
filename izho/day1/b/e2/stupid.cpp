//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, x, y;
  cin >> n >> x >> y;
  y += x;
  vector<int> ff(n);
  for (int i = 0; i < n; ++i) {
    cin >> ff[i];
  }

  function<long long(vector<int>, int, int)> f = [&](vector<int> a, int d, int start) {

    if ((int) a.size() == 1) {
      return 0LL;
    }  
    
    if ((int) a.size() == 2) {
      if (ff[start + a[0]] != ff[start + a[1]]) {
        return 0LL;
      }  

      return 0LL + y;
    }  

    vector<int> left, right;
    for (auto e : a) {
      if ((e >> d) & 1) {
        right.push_back(e);
      } else {
        left.push_back(e);
      }
    }

    return f(left, d + 1, start) + f(right, d + 1, start) + y;
    
  };

  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l, --r;
    vector<int> tt(r - l + 1);
    iota(tt.begin(), tt.end(), 0);
    cout << x + f(tt, 0, l) << '\n';
  }
}