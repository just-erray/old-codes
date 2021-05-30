// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int r, b, d;
    cin >> r >> b >> d;
    if (r > b) {
      swap(r, b);
    }
    cout << (1LL * r * (d + 1) >= b ? "YES" : "NO") << '\n';
  }
}