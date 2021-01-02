// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "nochange";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, k;
  cin >> k >> n;
  vector<int> c(k);
  for (int i = 0; i < k; ++i) {
    cin >> c[i];
  }

  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vector<int> pref(n + 1);
  for (int i = 0; i < n; ++i) {
    pref[i + 1] = pref[i] + a[i];
  }
  
  const int M = (1 << k);
  vector<int> dp(M, -1);
  int ans = -1;

  for (int i = 0; i < M; ++i) {
    if (dp[i] == n - 1) {
      int sum = 0;
      for (int j = 0; j < k; ++j) {
        sum += !((i >> j) & 1) * c[j];
      }

      ans = max(ans, sum);
      continue;
    }
    
    for (int j = 0; j < k; ++j) {
       if (((i >> j) & 1) == 0) {
         int next = i | (1 << j);
         dp[next] = max(dp[next], int(lower_bound(pref.begin(), pref.end(), pref[dp[i] + 1] + 1 + c[j]) - pref.begin()) - 2);       
       }
    }
  }
  cout << ans << '\n';
}