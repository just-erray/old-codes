// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  assert(n % 2 == 1);
  vector<vector<int>> ct((n + 1) / 2);
  for (int i = n / 2; i >= 0; --i) {
    const int size = i * 2 + 1;
    ct[i].resize(size);
    if (i == n / 2) {
      ct[i][m] = 1;
      continue;
    }

    for (int j = 0; j < size; ++j) {
      ct[i][j] = ct[i + 1][j] ^ ct[i + 2][j] ^ ct[i + 3][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    for (auto e : ct[i]) {
      cout << e << ' ';
    }

    cout << '\n';
  }
}