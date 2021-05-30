// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1));
  dp[0][0].push_back(0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (auto e : dp[i][j]) {
        dp[i + 1][j].push_back(e + (j + 1));
        dp[i][j + 1].push_back(e + (i + 1));
      } 
    }
  }
  sort(dp[n - 1][n - 1].begin(), dp[n - 1][n - 1].end());
  for (auto e : dp[n - 1][n - 1]) {
    cout << e << ' ';
  }
}