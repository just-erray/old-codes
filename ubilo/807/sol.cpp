// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "riv";
  freopen((P + ".gir").c_str(), "r", stdin);
  freopen((P + ".cik").c_str(), "w", stdout);
  #endif 
  int n, k;
  cin >> n >> k;
  ++k;
  vector<array<int, 3>> a(n + 1);
  vector<vector<int>> g(n + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 3; ++j) {
      cin >> a[i][j];
    }
    g[a[i][1]].push_back(i);
  }
                                                                                      
  const int long long = (int) 2e9 + 1;
  vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(n + 2, vector<long long>(k + 1)));
  vector<vector<int>> cost(n + 1, vector<int>(n + 2));
  vector<int> d(n);
  
  function<void(int)> Dfs = [&](int v) {
    for (auto u : g[v]) {
      d[u] = d[v] + 1;
      int w = a[u][2];
      for (int i = 0; i <= n; ++i) {
        cost[u][i + 1] = cost[v][i] + a[u][2];     
      }
      Dfs(u);
    }

    int size = a[v][0];
    for (int i = 0; i <= n + 1; ++i) {
      for (int j = 0; j <= k; ++j) {
        dp[v][i][j] = i * size; 
      }
    }

    for (int dis = 0; dis <= n; ++dis) {
            
    }

  };

  cout << dp[0][0][k] << '\n';
}