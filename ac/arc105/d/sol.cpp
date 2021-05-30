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
    if (n % 2 == 1) {
      cout << "Second";
    } else {
      sort(a.begin(), a.end());
      bool ok = true;
      for (int i = 0; i < n; i += 2) {
        ok &= (a[i] == a[i + 1]);
      }
      cout << (ok ? "Second" : "First");
    }
    cout << '\n';
  }
}