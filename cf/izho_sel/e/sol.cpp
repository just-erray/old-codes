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
    --a[i];
  }
 
  const int M = 20;
  const int X = (1 << M);
  vector<int> pos(M);
  vector<vector<long long>> cost(M, vector<long long>(M));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < M; ++j) {
      if (j == a[i]) {
        continue;
      } 
      cost[a[i]][j] += pos[j];
    }
    ++pos[a[i]];
  }

  const long long inf = (long long) 1e18;
  vector<long long> dp(X, inf);
  dp[X - 1] = 0;

  for (int mask = X - 2; mask >= 0; --mask) {
    vector<int> av;
    for (int i = 0; i < M; ++i) {
      if (((mask >> i) & 1) == 0) {
        av.push_back(i);
      }
    }

    for (auto i : av) {
      long long res = 0;
      for (auto j : av) {
        res += cost[i][j];
      }
      dp[mask] = min(dp[mask], res + dp[mask | (1 << i)]);
    }
  }

  cout << dp[0] << '\n';
}