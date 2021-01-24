// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int n = (int) s.size();
  string tmp = s;
  sort(tmp.begin(), tmp.end());
  tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = int(lower_bound(tmp.begin(), tmp.end(), s[i]) - tmp.begin());
  }

  const int M = (int) tmp.size();
  assert(M < 21);
  vector<vector<int>> bef(M, vector<int>(M));
  vector<int> add(M);

  for (int i = 0; i < n; ++i) {
    ++add[a[i]];
    if (i > 0) {
      ++bef[a[i]][a[i - 1]];
    }  
  }

  const int N = (1 << M);
  vector<int> dp(N, n + 1);
  dp[0] = 0;

  for (int i = 0; i < N; ++i) {
    for (int next = 0; next < M; ++next) {
      if ((i >> next) & 1) {
        continue;
      }

      int tot = add[next];
      for (int j = 0; j < M; ++j) {
        if ((i >> j) & 1) {
          tot -= bef[next][j];
        }
      }

      int g = (i | (1 << next));
      dp[g] = min(dp[g], dp[i] + tot);
    }
  }

  cout << dp.back() << '\n';
}