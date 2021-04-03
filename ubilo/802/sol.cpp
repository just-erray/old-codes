// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "kvec";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, q;
  string s;
  cin >> n >> q >> s;
  vector<vector<int>> g(q + 1);
  vector<pair<int, char>> qs(q + 1);
  for (int i = 1; i <= q; ++i) {
    int from;
    cin >> from >> qs[i].first >> qs[i].second;
    --qs[i].first;
    g[from].push_back(i);
  }

  vector<array<int, array<int, 2>, 2>> ct(q + 1);
  for (int i = 0; i < n; ++i) {
    int next = (i + 1) % n;
    ct[s[i] - '0'][s[next] - '0']++;
  }

  auto Add = [&](char c) {
    
  };

  vector<bool> ans(q + 1);
  function<void(int)> Dfs = [&](int v) {
     
  
    Add(old);
  };
  
  Dfs(0);
  for (int i = 1; i <= q; ++i) {
    cout << ans[i] ? "EVET" : "HAYIR" << '\n;'
  }
}