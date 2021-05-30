// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
struct dinics {
  struct edge {
    int v, u, flow, cap;
    edge(int _v, int _u, int _cap) : v(_v), u(_u), cap(_cap), flow(0) { }
  };

  vector<edge> es;
  vector<int> level;
  vector<int> p;
  vector<vector<int>> g;
  int s, t;

  dinics(int n, int _s, int _t) : s(_s), t(_t) {
    g.resize(n);
    p.resize(n);
    level.resize(n); 
  }

  bool bfs() {
    queue<int> que;
    que.push(s);
    fill(level.begin(), level.end(), -1);
    level[0] = 0;
    while (!que.empty()) {
      int v = que.front();
      que.pop();
      for (auto id : g[v]) {
        if (level[es[id].u] != -1 || es[id].flow == es[id].cap) {
          continue;
        }
        level[es[id].u] = level[v] + 1;
        que.push(es[id].u);
      }
    }
    return level[t] != -1;  
  }

  long long dfs(int v, long long mn) {
    if (mn == 0) {
      return 0;
    }
    if (v == t) {
      return mn;
    }
    for (int c& = p[v]; c < int(edges[v].size()); ++c) {
      int id = g[v][c];
      if (es[id].flow == es[id].cap || level[es[id].u] <= level[v]) {
        continue;
      }
      long long go = dfs(es[id].u, min(mn, es[id].cap - es[id].flow));
      if (go == 0) {
        continue;
      }
      edges[id].flow += 
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}