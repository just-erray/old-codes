// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  for (int tt = 0; tt < T; ++tt) {
    cout << "Case #:" << tt  + 1 << ": ";
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> a[i][j];
      }
    }
    vector<vector<int>> b(n vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> b[i][j];
      }
    }
    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
      cin >> r[i];
    }
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
      cin >> c[i];
    }
    for (int i = 0; i < n; ++i) {
      bool cur = false;
      for (int j = 0; j < n; ++j) {
        if (a[i][j] != -1) {
          cur ^= a[i][j];
        }
      } 
      r[i] ^= cur;
    }
    for (int i = 0; i < n; ++i) {
      bool cur = false;
      for (int j = 0; j < n; ++j) {
        if (a[j][i] != -1) {
          cur ^= a[i][j]; 
        }
      }
      c[i] ^= cur;
    }

  }
}