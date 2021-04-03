// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int n = (int) s.size();
  const int N = 16;
  vector<vector<long long>> cost(N, vector<long long>(N));
  for (int c = 0; c < 16; ++c) {
    char tar = 'a' + c;
    int cur = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == tar) {
        ++cur;
      } else {
        cost[s[i] - 'a'][c] += cur;
      }
    }
  }

  long long ans = 0;
  for (int mask = 0; mask < (1 << 16); ++mask) {
    long long cur = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (!((mask >> i) & 1) && ((mask >> j) & 1)) {
          cur += cost[i][j];
        }
      }
    }

    ans = max(ans, cur);
  }
  cout << ans << '\n';
}