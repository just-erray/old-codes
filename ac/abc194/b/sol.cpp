// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int ans = INT_MAX;
  int mx, my;
  mx = my = (int) 1e6;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    ans = min({ans, x + y, max(mx, y), max(my, x)});
    mx = min(x, mx);
    my = min(y, my);
  }
  cout << ans << '\n';
}