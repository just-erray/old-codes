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

  vector<vector<int>> dp(n, vector<int>(n));

  auto Get = [&](int x, int y) {
    if (x > y) {
      return 0;
    }

    return dp[x][y];
  };

  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
  }

  for (int l = 1; l <= n; ++l) {
    for (int i = 0; i < n - l; ++i) {
      dp[i][i + l] = max(Get(i, i + l - 1), Get(i + 1, i + l));
      if (a[i] == a[i + l]) {
        dp[i][i + l] = max(dp[i][i + l],  max(dp[i][i + l], Get(i + 1, i + l - 1)) + 2);
      }
    }
  }


  cout << dp[0][n - 1] << '\n';
}

