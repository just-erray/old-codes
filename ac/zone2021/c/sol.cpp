// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<array<int, 5>> a(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 5; ++j) {
      cin >> a[i][j];
    }
  }
  int ans = 0;
  for (int t = 0; t < 5; ++t) {
    sort(a.begin(), a.end(), [&](auto x, auto y) {
      return x[t] < y[t];
    });
    for (int i = 2; i < n; ++i) {
      vector<bitset<5>> can(n);      
      for (int j = 0; j <= i; ++j) {
        for (int take = 0; take < 5; ++take) {
          can[j][take] = (a[j][take] >= a[i][t]);
        }
      }
      
    }
  }
  cout << ans << '\n';
}