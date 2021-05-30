// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  vector<vector<int>> mat(n, vector<int>(m, 0));
  queue<array<int, 3>> que;  
  vector<pair<int ,int>> start;
  vector<vector<vector<bool>>> vis(n, vector<vector<bool>>(m, vector<bool>(4)));
  for (int i = 0; i < a; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    mat[x][y] = 1;
    start.emplace_back(x, y);
    for (int d = 0; d < 4; ++d) {
      vis[x][y][d] = true;
      que.push({x, y, d});
    }
  }

  for (int i = 0; i < b; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    mat[x][y] = -1;
  }

  auto aor = [&](int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= m);
  };   
  vector<vector<bool>> ok(n, vector<bool>(m));
  while (!que.empty()) {
    auto[x, y, d] = que.front();
    que.pop();
    int nx = x + dx[d];
    int ny = y + dy[d];
    if (vis[nx][ny][d]) {
      continue;
    }
    ok[x][ny] = true;
    vis[nx][ny][d] = true;

  }
}
