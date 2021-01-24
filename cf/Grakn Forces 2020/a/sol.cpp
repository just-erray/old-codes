// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<vector<int>> a(3, vector<int>(n));
    for (int j = 0; j < 3; ++j) {
      for (int i = 0; i < n; ++i) {
        cin >> a[j][i];
      }
    }
    int lst = -1;
    int ans0 = -1;
    for (int i = 0; i < n; ++i) {
      int res = -1;
      for (int j = 0; j < 3; ++j) {
        if (lst != a[j][i] && (i != n - 1 || ans0 != a[j][i])) {
          res = a[j][i];
        }    
      }
      cout << res << ' ';
      if (i == 0) ans0 = res;
      lst = res;
    }
    cout << '\n';
  }
}