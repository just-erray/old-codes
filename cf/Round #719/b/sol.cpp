// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 1; i < 10; ++i) {
      long long cur = i;
      while (cur <= n) {
        ++ans;
        (cur *= 10) += i;
      }
    }
    cout << ans << '\n';
  }
}