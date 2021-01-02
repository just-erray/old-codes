// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "empty";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 

  int n, k;
  cin >> n >> k;
  vector<int> ct(n);

  for (int i = 0; i < k; ++i) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    for (int f = 1; f <= y; ++f) {
      ct[int((1LL * a * f + b) % n)] += x;
    }
  }

  int now = 0;
  vector<bool> vis(n);
  for (int i = 0; i < n; ++i) {
    now += ct[i];
    if (now > 0) {
      --now;
      vis[i] = true;
    } 
  }

  int ans = -1;
  for (int i = 0; i < n; ++i) {
    if (vis[i]) {
      continue;
    }

    if (now > 0) {
      --now;
    } else {
      ans = i;
      break;
    }
  }

  cout << ans << '\n';
  
}