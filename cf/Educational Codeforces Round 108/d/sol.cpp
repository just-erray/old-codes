// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }

  auto Mul = [&](int x, int y) {
    return 1LL * a[x] * b[y];
  };

  vector<long long> pref(n + 1);
  for (int i = 0; i < n; ++i) {
    pref[i + 1] = pref[i] + Mul(i, i);
  }
  vector<long long> suf(n + 1);
  for (int i = n; i > 0; --i) {
    suf[i - 1] = suf[i] + Mul(i - 1, i - 1);
  }

  vector<vector<long long>> dp(n, vector<long long>(n));
  
  for (int i = 0; i < n; ++i) {
    dp[i][i] = Mul(i, i);
  }
  for (int len = 1; len < n; ++len) {
    for (int i = 0; i < n - len; ++i) {
      int j = i + len;
      dp[i][j] = dp[i + 1][j - 1] + Mul(i, j) + Mul(j, i);
    }  
  }

  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      ans = max(ans, dp[i][j] + pref[i] + suf[j + 1]);
    }
  }
  cout << ans << '\n';
}