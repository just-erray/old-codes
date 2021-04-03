// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  const int BLOCK = int(sqrt(n)) + 1;
  const int b_size = n / BLOCK + 1;

  vector<vector<array<int, 3>>> qs(b_size);
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    qs[l / BLOCK].push_back({l, r, i});
  }

  const int N = (int) 1e6 + 1;
  vector<int> ct(N);
  for (auto fi : qs) {
    if (fi.empty()) {
      continue;
    }
    sort(fi.begin(), fi.end(), [&](auto x, auto y) {
      return x[1] < y[1];
    });
    int lst_l = fi[0][1] + 1, lst_r = fi[0][1];
    for (auto[l, r] : fi) {
      while (lst_l >= l) {
        Add(
        --lst_l;
      } 
    }
  }
}