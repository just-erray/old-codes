// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "vacationgold";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, m, k, q;
  cin >> n >> m >> k >> q;
  vector<vector<vector<pair<int, int>>>> g(2, vector<vector<pair<int, int>>>(n));

  for (int i = 0; i < m; ++i) {
    int x, y, w;
    cin >> x >> y >> w;
    --x, --y;
    g[0][x].emplace_back(y, w);
    g[1][y].emplace_back(x, w);
  }

  vector<int> hub(k);
  for (int i = 0; i < k; ++i) {
    cin >> hub[i];
    --hub[i];
  }
  
  vector<int> id(n, -1);
  for (int i = 0; i < k; ++i) {
    id[hub[i]] = i;
  }

  const int inf = (int) 6e8;
  vector<vector<vector<int>>> sp(2, vector<vector<int>>(k, vector<int>(n, inf)));
  
  for (int i = 0; i < k; ++i) {
    int me = hub[i];
    for (int j = 0; j < 2; ++j) {
      sp[j][i][hub[i]] = 0;  
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
      pq.emplace(0, me);
      vector<bool> vis(n);

      while (!pq.empty()) {
        int cost, v;
        tie(cost, v) = pq.top();
        pq.pop();
        if (vis[v] || cost > sp[j][i][v]) {
          continue;
        }
        vis[v] = true;

        for (int foo = 0; foo < (int) g[j][v].size(); ++foo) {
          int u, w;
          tie(u, w) = g[j][v][foo];
          if (cost + w < sp[j][i][u]) {
            sp[j][i][u] = cost + w;
            pq.emplace(cost + w, u);
          }
        }
      }
    }    
  }

  long long res = 0;
  int ct = 0;
  while (q--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    int ans = inf;
    for (int i = 0; i < k; ++i) {
      ans = min(ans, sp[0][i][y] + sp[1][i][x]);
    }
    
    if (ans < inf) {
      res += ans;
      ++ct;
    }
  }
  cout << ct << '\n' << res << '\n';
}