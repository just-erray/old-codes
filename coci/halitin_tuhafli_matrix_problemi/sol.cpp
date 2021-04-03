// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> mat(n);
  for (int i = 0; i < n; ++i) {
    cin >> mat[i];
  }


  vector<vector<int>> best(n, vector(m, 0));
  for (int i = 0; i < n; ++i) {
    vector<vector<bool>> dp(m, vector(m, true));
    for (int len = 1; len <= m; ++len) {
      for (int j = 0; j < n - len; ++j) {
        dp[j][j + len] = dp[j + 1][j + len - 1] && (mat[i][j] == mat[i][j + len]);
      }
    }
    for (int j = 0; j < m; ++j) {
      for (int k = j; k < m; ++k) {
        if (dp[j][k]) {
          best[i][j] = k - j + 1;
        }
      }
    }
  }
  
  int ans = -1;
  for (int j = 0; j < n; ++j) {
    vector<vector<bool>> dp(n, vector(n, true));
    for (int len = 1; len <= n; ++len) {
      for (int i = 0; i < n - len; ++i) {
        dp[i][i + len] = dp[i + 1][i + len - 1] && (mat[i][j] == mat[i + len][j]);
      }
    } 
    for (int i = 0; i < n; ++i) {
      int mn = 1000;
      for (int k = i; k < n; ++k) {
        mn = min(best[i][j], mn);
        if (dp[i][k] && mn >= k - i + 1) {
          ans = max(ans, k - i + 1);
        }
      }
    }

  }
  cout << ans << '\n';
}