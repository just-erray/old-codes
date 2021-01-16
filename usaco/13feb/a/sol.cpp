// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "rblock";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, m;
  cin >> n >> m;

  const int inf = (int) 1e8;
  vector<vector<int>> g(n);
  vector<array<int, 3>> edges(m);
  for (int i = 0; i < m; ++i) {
    int x, y, w;
    cin >> x >> y >> w;
    --x, --y;
    g[x].emplace_back(i);
    g[y].emplace_back(i);
    edges[i] = {x, y, w};
  }

  auto djikstra = [&] {
    vector<int> sp(n, inf);
    vector<bool> vis(n);
    vector<int> res;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.emplace(0, 0, -1);

    while (!pq.empty()) {
      int cost, v, from;
      tie(cost, v, from) = pq.top();
      pq.pop();

      if (vis[v] || sp[v] < cost) {
        continue;
      }

      if (from > 0) {
        res.push_back(from);
      }

      vis[v] = true;

      for (auto id : g[v]) {
        int u = v ^ edges[id][0] ^ edges[id][1];
        int w = edges[id][2];
        int nCost = cost + w;

        if (!vis[u] && nCost < sp[u]) {
          sp[u] = nCost;
          pq.emplace(nCost, u, id);
        }
      }
    }

    return make_pair(sp.back(), res);
  };

  int first;
  vector<int> route;
  tie(first, route) = djikstra();
  int best = first;

  for (auto id : route) {
    edges[id][2] *= 2;
    best = max(best, djikstra().first);
    edges[id][2] /= 2;      
  }

  cout << best - first << '\n';
}
