// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  long long m;
  cin >> n >> k >> m;
  vector<int> id(n);
  iota(id.begin(), id.end(), 0);
  vector<vector<pair<int, int>>> go(n);
  for (int i = 0; i < n; ++i) {
    go[i].emplace_back(i, 0);
  }

  for (int i = 0; i < k; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    swap(id[x], id[y]);
    go[id[x]].emplace_back(x, i + 1);
    go[id[y]].emplace_back(y, i + 1);
  }

  vector<int> dir(n);
  for (int i = 0; i < n; ++i) {
    dir[id[i]] = i;
  }

  vector<vector<int>> g;
  vector<bool> vis(n);

  for (int i = 0; i < n; ++i) {
    if (vis[i]) {
      continue;
    }  

    int v = i;
    vector<int> add;
    while (!vis[v]) {
      add.push_back(v);
      vis[v] = true;
      v = dir[v];
    }

    g.push_back(add);
  }

  vector<int> ans(n);

  auto solve = [&](vector<int> x) {
    int size = (int) x.size();
    long long be = min(m, 1LL * k * size - 1);
    map<int, int> freq;
    int res = 0;

    auto add = [&](int xx, int y) {
      int nw = (freq[xx] += y);
      if (nw == 0) {
        --res;
      } else if (nw == 1 && y == 1) {
        ++res;
      }
    };

    
    int gob = be / k;
    int left = be % k;
    for (int i = 0; i < gob; ++i) {
      for (auto[nw, foo] : go[x[i]]) {
        add(nw, 1); 
      } 
    }

    for (auto[nw, foo] : go[x[gob]]) {
      if (foo <= left) {
        add(nw, 1);
      }
    }

    ans[x[0]] = res;
    for (int i = 1; i < size; ++i) {
      int next = (i + gob) % size;
      int bef = (next - 1 + size) % size;
      
      for (auto[nw, foo] : go[x[bef]]) {
        if (foo > left) {
          add(nw, 1);
        }
      }

      for (auto[nw, foo] : go[x[i - 1]]) {
        add(nw, -1);
      }

      for (auto[nw, foo] : go[x[next]]) {
        if (foo <= left) {
          add(nw, 1);
        }
      }

      ans[x[i]] = res;
    }
  };
  
  for (auto e : g) {
    solve(e);
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << '\n';
  }
}