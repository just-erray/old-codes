// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  auto solve = [&](int l, int r) {
    vector<int> dp(r);
    dp[l] = a[l];
    for (int i = l + 1; i <= r; ++i) {
      dp[i] = dp[i - 1] + a[i];
      if (i > l + 1) {
        dp[i] = max(dp[i], (i == l + 2 ? 0 : dp[i - 3]));
      }
    }
    return dp[r];
  };
  
  vector<int> dp(n);
  vector<int> pref(n);
  for (int i = 0; i < n; ++i) {
    for (int j = i - 2; j >= 0; j -= 3) {
      dp[i] = max(dp[i], (j == 0 ? 0 : pref[j - 1]) + solve(j, i));
    }
    pref[i] = max(dp[i], (i == 0 ? 0 : pref[i - 1]));
  }
  cout << pref[n - 1] << '\n';
}