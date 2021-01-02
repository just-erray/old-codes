// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, (long long) 1e12));
  fill(dp[n].begin(), dp[n].end(), 0);

  for (int i = n - 1; i >= 0; --i) {
    for (int j = 1; j <= k; ++j) {
          
    }
  }
}