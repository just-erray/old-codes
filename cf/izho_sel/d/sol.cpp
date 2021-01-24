// author: erray
#include<bits/stdc++.h>
 
using namespace std;

 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vector<vector<int>> gap;
  vector<int> size;
  auto Ok = [&](auto x) { 
    if ((int) gap.size() > 3) {
      cout << -1 << '\n';
      exit(0);
    }

    int cur = 0;
    for (auto el : gap) {
      if (el == x) { 
        ++size[cur];
        return cur;
      }
      ++cur;
    }
    
    return -1;
  };
  
  for (int i = 0; i < n; ++i) {
    sort(g[i].begin(), g[i].end());
    if (Ok(g[i]) == -1) {
      gap.push_back(g[i]);
      size.push_back(1);
    }
  }
  bool ok = ((int) gap.size() == 3);
  
  for (int i = 0; i < (int) gap.size(); ++i) {
    ok &= (size[i] == n - (int) gap[i].size());
  }

  if (!ok) {
    return cout << -1, 0;
  }

  for (int i = 0; i < n; ++i) {
    cout << 1 + Ok(g[i]) << ' '; 
  }
}