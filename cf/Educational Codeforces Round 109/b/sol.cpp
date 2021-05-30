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
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    if (is_sorted(a.begin(), a.end())) {
      cout << 0 << '\n';
      continue;
    }
    cout << (a[0] == 1 || a[n - 1] == n ? 1 : 2) << '\n';
  }
}