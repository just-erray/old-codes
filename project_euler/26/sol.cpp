// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int best = 1;
  int ans = 1;
  for (int i = 1; i < n; ++i) {
    vector<bool> vis(i + 1);
    int cur = 1;
    while (!vis[cur]) {
      vis[cur] = true;
      cur *= 100000;
      cur %= i;
    }
    if (accumulate(vis.begin(), vis.end(), 0) > best) {
      best = accumulate(vis.begin(), vis.end(), 0);
      ans = i;
    }
  }
  cout << ans << '\n';
}