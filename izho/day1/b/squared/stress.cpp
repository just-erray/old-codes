//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = (int) 1e3;
  cout << n << ' ' << (int) 1e9 << (int) 1e9 << '\n';
  for (int i = 0; i < n; ++i) {
    cout << (n - i) << ' ';
  }
  cout << 0;
}