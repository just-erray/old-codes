// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> store(n);
  for (int i = 0; i < m; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    --x, --y;
    store[x].emplace_back(y, z);
  }
  
  const int N = 1 << n;
  vector<long long> dp(N);
  dp[0] = 1;
  for (int it = 0; it < n; ++it) {
    vector<long long> new_dp(N);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < n; ++j) {
        if ((i >> j) & 1) {
          continue;
        }
        new_dp[i | (1 << j)] += dp[i];
      }
    }

    swap(dp, new_dp);
    for (auto[y, z] : store[it]) {
      for (int i = 0; i < N; ++i) {
        if (__builtin_popcount(((1 << (y + 1)) - 1) & i) > z) {
          dp[i] = 0;
        }
      }
    }
  }

  cout << dp[N - 1] << '\n';
}