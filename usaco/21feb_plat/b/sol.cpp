// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) { 
      int x, y;
      cin >> x >> y;
      --x, --y;
      g[x].push_back(y);
      g[y].push_back(x);
      x
    }
  }
}