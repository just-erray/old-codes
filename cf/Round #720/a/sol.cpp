// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int a, b;
    cin >> a >> b;
    if (b == 1) {
      cout << "NO\n";
      continue;
    }
    cout << "YES\n";
    if (b % 2 == 0) {
      cout << a << ' ' << 1LL * a * b * 2 - a << ' ' << 1LL * a * b * 2 << '\n';
    } else {
      cout << a << ' ' << 1LL * a * b - a << ' ' << 1LL * a * b << '\n';
    }
  }
}