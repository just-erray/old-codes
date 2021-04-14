// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> mat(n);
  for (int i = 0; i < n; ++i) {
    cin >> mat[i];
  }
  const int di[] = {1, -1, 0, 0}, dj[] = {0, 0, 1, -1}; 
  vector<vector<pair<int, int>>> all;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] != 'G') {
        continue;
      }
      vector<pair<int, int>> add;
      for (int d = 0; d < 4; ++d) {
        int ni = i + di[d], nj = j + dj[d];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && mat[ni][nj] == 'C') {
          add.emplace_back(ni, nj);
        }
      }
      sort(add.begin(), add.end());
      if (int(add.size()) > 1) {
        all.push_back(add);
      }
    }
  }
  sort(all.begin(), all.end());
  all.erase(unique(all.begin(), all.end()), all.end());
  cout << (int) all.size() << '\n';
}