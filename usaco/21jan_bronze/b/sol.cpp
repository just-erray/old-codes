// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> ct(2);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    ++ct[x % 2];
  }

  int ans = 1;
  for (int i = 0; i <= n; ++i) {
    if (i <= ct[1] && (ct[1] - i) % 2 == 0) {
      int odd = i;
      int even = ct[0] + (ct[1] - i) / 2;
      if (odd > even) {
        continue;
      }

      even = min(even, odd + 1);
      ans = max(ans, even + odd); 
    } 
  }

  cout << ans << '\n';
}