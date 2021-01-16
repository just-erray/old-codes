//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, s, t;
  cin >> n >> s >> t;
  --s, --t;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  
  if (s > t) {
    s = n - s - 1;
    t = n - t - 1;
    reverse(a.begin(), a.end());
  }

  vector<long long> dp(n);  
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int x, int y) {
    return a[x] > a[y];
  });

  for (int i = 0; i < n; ++i) {
    dp[i] = 1LL * abs(i - s) * a[s];
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      dp[ord[j]] = min(dp[ord[j]], dp[ord[i]] + 1LL * abs(ord[i] - ord[j]) * a[ord[i]]);
    }
  }

  long long ans = LLONG_MAX;
  for (int i = 0; i < n; ++i) {
     //cerr << dp[i] << ' ';
    ans = min(ans, dp[i] + 1LL * abs(i - t) * a[i]); 
  }
  cout << ans << '\n';
}