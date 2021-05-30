// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int sx, sy;
  int tx, ty;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      
    }
  }
  const int INF = n * n + 37;
  deque<pair<int, int>> que;
  vector<vector<int>> sp(n, vector<int>(m, INF));
  vector<int> sp(26);
  const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
  while (!que.empty()) {
    auto[x, y] = que.front();
  }
}