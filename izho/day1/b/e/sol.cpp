//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, x, y;
  cin >> n >> x >> y;
  vector<int> foo(n);
  for (int i = 0; i < n; ++i) {
    cin >> foo[i];
  }
  y += x;
  vector<long long> ans(n + 1);
  ans[1] = 0;
  for (int i = 2; i <= n; ++i) {
    ans[i] = ans[i - (i / 2)] + ans[(i / 2)] + y;
  }

  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << ans[r - l + 1] + x << '\n';
  }
}