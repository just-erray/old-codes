// author: erray
#include<bits/stdc++.h>
 
using namespace std;
struct Dinics {
  int start, end;
  long long res = 0;
  struct edge {
    int to, cap;
    int flow = 0;
  };                               
  
  vector<vector<edge>> g;
  vector<int> level;
  Dinics(int _start, int _end, int n) : start(_start), end(_end) {
    level.assign(n, -1);
    g.assign(n, vector<edge>());
  }

  void add(int v, int u, int cap) {
    g[v].push_back(edge{u, cap});
    g[u].push_back(edge{v, cap});
  }

  bool bfs() {
    queue<int> que;
    level.assign((int) level.size(), -1);
    que.push(start);
    level[start] = 0;
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (auto[u, cap, flow] : g[v]) {
        if (level[u] != -1 && flow < cap) {
          level[u] = level[v] + 1;
          que.push(u);
        }
      }
    }
    return level[end] != -1;
  }

  int dfs(int v, int aug) {
    if (v == end || aug == 0) {
      return aug;
    }  
    for (auto[u, cap, flow] : g[v]) {
      if (cap == flow || level[u] != level[v] + 1) {
        continue;
      }
      int a = dfs(u, min(aug, cap - flow));
      if (a) {
        flow += a;
        if (v == start) {
          res += a; 
        }
        return a;
      } else {
        flow = cap;
      }
    }
    return 0;
  }

  long long get() {
    while (!bfs()) {
      dfs(0, INT_MAX);
    }

    return res;
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  Dinics flow(0, n - 1, n);
  while (m--) {
    int x, y, c;
    cin >> x >> y >> c;
    --x, --y;
    flow.add(x, y, c);
  }
  cout << flow.get() << '\n';
}