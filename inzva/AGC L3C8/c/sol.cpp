// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  queue<pair<int, int>> que;
  vector<vector<bool>> vis(n, vector<bool>(m));
  vector<vector<int>> cost(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char c;
      cin >> c;
      if (c == '#') {
        que.emplace(i, j);
        vis[i][j] = true;
        cost[i][j] = 0;
      }
    }
  }
  int ans = 0;            
  const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
  while (!que.empty()) {
    int x, y;
    tie(x, y) = que.front();
    que.pop();
    ans = max(ans, cost[x][y]);
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d];
      int ny = y + dy[d];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m || vis[nx][ny]) {
        continue;
      } 
      cost[nx][ny] = cost[x][y] + 1;
      vis[nx][ny] = true;
      que.emplace(nx, ny);
    }
  }
  cout << ans << '\n';
}