// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<bool> a(n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    a[i] = (s[0] == 'O');
  }

  vector<long long> dp(2, 1);
  for (int i = 0; i < n; ++i) {
    vector<long long> new_dp(2, 0);
    if (a[i]) {
      new_dp[1] = dp[1] * 2 + dp[0];
      new_dp[0] = dp[0];
    } else {
      new_dp[1] = dp[1];
      new_dp[0] = dp[1] + dp[0] * 2;
    }
    swap(dp, new_dp);
  }

  cout << dp[1] << '\n';
}