// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int l = (1 << (n - 1));
  cout << l << '\n';
  for (int i = 0; i < l; ++i) {
    cout << n << ' ' << i + 1 << '\n';
  }
}