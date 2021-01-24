// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    string ans;
    while ((int) ans.size() < n) {
      for (int j = 0; j < k && (int) ans.size() < n; ++j) {
        ans += 'a' + j;
      }
    }
    cout << ans << '\n';
  }
}