// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  const int N = int(1e4);
  vector<int> ans = {6, 3};
  vector<bool> ip(N + 1, true);
  for (int j = 2; j <= N / 2; ++j) {
    if (!ip[j]) {
      continue;
    }
    if (ans[1] * j > N) {
      break;
    }
    if (j > 3) {
      //cerr << j << '\n';
      ans[1] *= j;
    }
    for (int i = j + j; i <= N; i += j) {
      ip[i] = false; 
    }
  }

  for (int i = 10; i <= N; i += 2) {
    if (gcd(i, ans[1]) > 1) {
      ans.push_back(i);
    }
  }

  cerr << int(ans.size()) << ' ' << gcd(gcd(ans[0], ans[1]), ans[2]) << '\n';

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
  }
}