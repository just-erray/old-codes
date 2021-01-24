// author: erray
#include<bits/stdc++.h>

using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  vector<array<int, 3>> edges(m);
  for (int i = 0; i < m; ++i) {
    cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    --edges[i][0], --edges[i][1];
    g[edges[i][0]].push_back(i);
    g[edges[i][1]].push_back(i);
  }

  vector<bool> in(m, false);

  auto solve = [&](int x) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.emplace(0, x, -1);
    
    const int inf = (int) 1e9;
    vector<int> cost(n, inf);
    vector<bool> vis(n);
    cost[x] = 0;

    while (!pq.empty()) {
      auto[c, v, f] = pq.top();
      pq.pop();               

      if (cost[v] < c) {
        continue;
      }

      if (f >= 0) {
        in[f] = true;
      }

      if (vis[v]) {
        continue;  
      }

      vis[v] = true;
      for (auto id : g[v]) {
        int w = edges[id][2];
        int next = edges[id][0] ^ v ^ edges[id][1];
        if (vis[next] || c + w > cost[next]) {
          continue;  
        }
        cost[next] = c + w;
        pq.emplace(cost[next], next, id);
      }
    }
  };


  for (int i = 0; i < n; ++i) {
    solve(i);
  }

  cout << m - accumulate(in.begin(), in.end(), 0) << '\n';
}