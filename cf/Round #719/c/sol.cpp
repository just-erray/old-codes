// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    array<vector<pair<int, int>>, 2> av;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        av[(i + j) % 2].emplace_back(i, j);
      }
    }
    if (n == 2) {
      cout << -1 << '\n';
      continue;
    }

    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n * n; ++i) {
      if (av[0].empty()) {
        swap(av[0], av[1]);
      }  
      ans[av[0].back().first][av[0].back().second] = i;
      av[0].pop_back();
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << ans[i][j] + 1 << ' ';
      }
      cout << '\n';
    }
  }
}