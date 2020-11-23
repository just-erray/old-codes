// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  array<int, 26> cost;
  for (int i = 0; i < 26; ++i) {
    cin >> cost[i];
  }
  string a, b;
  cin >> a >> b;
  vector<vector<int>> pos(26);
  for (auto& c : a) {
    c -= 'a';
  }
  
  int ind = 0;
  for (auto& c : b) {
    c -= 'a';
    pos[c].push_back(ind++);
  }
  vector<long long> dp(m + 1);
  for (int i = n - 1; i >= 0; --i) {
    vector<long long> new_dp = dp;
    for (int j = m - 1; j >= 0; --j) {
      auto next = lower_bound(pos[a[i]].begin(), pos[a[i]].end(), j);
      if (next != pos[a[i]].end()) {
        int go = *next;
        new_dp[j] = max(new_dp[j], dp[go + 1] + cost[a[i]]);
      }      
    }

    swap(dp, new_dp);
  }
  cout << dp[0] << '\n';
}