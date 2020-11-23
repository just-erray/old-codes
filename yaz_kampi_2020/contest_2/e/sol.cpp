// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  const int N = (int) 1e5 + 1;
  vector<int> dp(N, (int) 1e6);
  dp[0] = 0;
  for (int j = 0; j < N; ++j) {
    for (int i = 1; i * i * i <= j; ++i) {
      dp[j] = min(dp[j], dp[j - i * i * i] + 1);
    }
  }
  int cs = 0; 
  int x;
  while (scanf("%d",&x)!=EOF) {
    //cerr << x << ' ';
    cout << "Case #" << ++cs << ": " << dp[x] << '\n';
  }
}