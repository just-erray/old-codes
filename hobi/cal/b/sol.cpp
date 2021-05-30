// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> mat(n);
  for (int i = 0; i < n; ++i) {
    mat[i].resize(i + 1);
    for (int j = 0; j <= i; ++j) {
      cin >> mat[i][j];
      --mat[i][j];
    }
  }

  vector<int> ans;
  function<void(int, int, vector<int>)> Dfs = [&](int x, int y, vector<int> lst) {
    lst.push_back(mat[x][y]);
    if (x == n - 1) {
      if (set<int>(lst.begin(), lst.end()).size() == n) {
        assert(ans.empty());
        ans = lst;
      }
      return;
    }
    Dfs(x + 1, y, lst);
    Dfs(x + 1, y + 1, lst);
  };
  Dfs(0, 0, vector<int>(0, 0));
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
}