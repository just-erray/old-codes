// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k, t;
  cin >> n >> k >> t;
  vector<string> mat(n);
  for (int i = 0; i < n; ++i) {
    cin >> mat[i];
  }
  
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, (int) 1e9));
  dp[0][0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int next = dp[i][j] + ((mat[i][j] == 'X') || dp[i][j] % t);
      dp[i + 1][j] = min(dp[i + 1][j], next);
      dp[i][j + 1] = min(dp[i][j + 1], next);
    }
  } 

  int ans = dp[n - 1][n - 1];
  cout << 2 * (n - 1) + (ans / t + !!(ans % t)) * k  << '\n';
}