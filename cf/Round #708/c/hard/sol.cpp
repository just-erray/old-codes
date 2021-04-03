// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> k >> n;
    if (n < 5) {
  
    } else {
      vector<int> ans(n, 1);
      if (k % 2 == n % 2) {
        ans[0] = ans[1] = (k - (n - 2)) / 2;
      } else {
        
      }
      for (auto e : ans) {
        cout << e << ' ';
      }
    }
    cout << '\n';
  }
}