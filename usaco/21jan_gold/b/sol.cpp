// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
#define int int64_t

int32_t main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i];        
    --c[i];
  }

  vector<vector<bool>> can(k, vector<bool>(k));
  for (int i = 0; i < k; ++i) {
    string foo;
    cin >> foo;
    for (int j = 0; j < k; ++j) {
      can[i][j] = (foo[j] == '1');   
    }
  }
  
  vector<vector<int>> pos(k);
  for (int i = 0; i < n; ++i) {
    pos[c[i]].push_back(i);
  }
  
  vector<vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j) {
      if (!can[j][c[i]] || pos[j].empty()) {
        continue;
      }

      if (pos[j][0] < i) {
        int next = *prev(lower_bound(pos[j].begin(), pos[j].end(), i));
        g[next].push_back(i);
      }

      auto next = lower_bound(pos[j].begin(), pos[j].end(), i + 1);
      if (next != pos[j].end()) {
        g[*next].push_back(i);
      }
    }
  }


  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;


  vector<bool> vis(n);
  vector<long long> sp(n, LLONG_MAX);
   auto add = [&](int v, long long x) {
    if (vis[v] || sp[v] < x) {
      return;
    }

    sp[v] = x;
    pq.emplace(x, v);
  };

  add(0, 0);
  
  while (!pq.empty()) {
    long long cost;
    int v;
    tie(cost, v) = pq.top();
    pq.pop();
     
    if (vis[v]) {
      continue;
    }

    vis[v] = true;

    for (auto u : g[v]) {
      assert(u != v);
      add(u, cost + abs(u - v));
    }
  }

  cout << (vis[n - 1] ? sp[n - 1] : (long long) -1) << '\n';
}