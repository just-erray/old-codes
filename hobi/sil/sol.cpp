// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  const int N = (1 << n);
  vector<bool> dp(N);
  dp[N - 1] = true;
  for (int i = N - 2; i >= 0; --i) {
    bool can = true;
    for (int j = 0; j < n; ++j) {
      if ((i >> j) & 1) {
        continue;
      }

      int nw = i;
      for (int add = 0; add <= j; ++add) {
        if ((j + 1) % (add + 1) == 0) {
          nw |= (1 << add);
        }
      }
      
      can &= (dp[nw]);
    }

    if (can) {
      dp[i] = false;
    }
  }

  cout << dp.back() << '\n';
}