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
  }
  vector<int> ones;
  for (int i = 0; i < n; ++i) {
    if (a[i]) {
      ones.push_back(i);
    }
  }
  
  const int pl = (int) ones.size();
  const int n2 = n * (n - 1) / 2 + 1;

  vector<vector<vector<int>>> dp(1, vector<vector<int>>(1, vector<int>(n2)));
  for (int i = 0; i < n; ++i) {
    const int bn = min(i + 1, (int) pl.size()) + 1;
    vector<vector<vector<int>>> newDp(i + 2, vector<vector<int>>(bn, vector<int>(n2)));    
    for (int j = 0; j < i + 2; ++j) {
      for (int z = 0; z < bn; ++z) {
        for (int left = 0; left < n2; ++left) {
          {
            
          }
          {
          
          }
        }
      }
    }  
    swap(newDp, dp);
  }
  vector<int> ans(n2);
  for (int i = 0; i < n; ++i) {
    ans[i] = max(ans[i - 1], dp[0][0][i]);
  }
  
  for (auto el : ans) {
    cout << el << ' ';
  }
}