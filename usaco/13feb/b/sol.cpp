// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "dec";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, b;
  cin >> n >> b;
  vector<vector<pair<int, int>>> bonus(n);

  for (int i = 0; i < b; ++i) {
    int k, p, a;
    cin >> k >> p >> a;
    --k;
    bonus[k].emplace_back(p, a);
  }
  
  for (int i = 0; i < n; ++i) {
    sort(bonus[i].begin(), bonus[i].end());
  }

  vector<vector<int>> mat(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> mat[i][j];
    }
  }

  const int M = (1 << n);
  vector<vector<int>> group(n + 1);
  for (int i = 0; i < M; ++i) {
    group[__builtin_popcount(i)].push_back(i);
  }

  const int inf = (int) 1e9;
  vector<int> dp(M, -inf);
  dp[0] = 0;

  for (int e = 0; e < n; ++e) {
    for (auto mask : group[e]) {
      for (int i = 0; i < n; ++i) {
        if (((mask >> i) & 1) == 1) {
          continue;
        }
        
        int res = dp[mask] + mat[i][e];
        for (int j = 0; j < (int) bonus[e].size(); ++j) {
          if (res >= bonus[e][j].first) {
            res += bonus[e][j].second;
          }
        }

        int next = mask | (1 << i); 
        dp[next] = max(dp[next], res); 
      }
    }  
  }

  cout << dp.back() << '\n';
}