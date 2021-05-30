// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  long double x;
  cin >> n >> x;
  int ans = -1;
  for (int i = 0; i < n; ++i) {
    int v, p;
    cin >> v >> p;
    if (ans != -1) {
      continue;
    }

    x -= (long double) v * p / 100;
    if (x <= 0) {
      ans = i + 1;    
    }
  }
  cout << ans << '\n';
}