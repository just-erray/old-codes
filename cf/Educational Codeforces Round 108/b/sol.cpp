// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, m, k;
    cin >> n >> m >> k;
    cout << (k == m - 1 + ((n - 1) * m) ? "YES" : "NO") << '\n';
  }
}