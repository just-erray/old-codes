// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> mat(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }
  
  vector<int> no_match;
  for (int i = 0; i < m; ++i) {
    if (mat[0][i] != mat[1][i]) {
      no_match.push_back(i);
    }
  }
  
  auto my_assert = [&](bool x) {
    if (!x) {
      cout << "No\n";
      exit(0);
    }
  };

  my_assert(int(no_match.size()) <= 4);
  
}