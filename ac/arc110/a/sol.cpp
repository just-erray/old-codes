// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  long long ans = 1;
  for (int i = 2; i <= n; ++i) {
    ans = lcm(ans, i);  
  }

  cout << ans + 1 << '\n';
}