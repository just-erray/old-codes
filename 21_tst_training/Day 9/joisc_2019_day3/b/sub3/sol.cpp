// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string a, b;
  cin >> n >> a >> b;
  assert(count(a.begin(), a.end(), '0') == n);
  int ans = 0;
  for (int i = 1; i < n; ++i) {
    if (b[i] == '1' && b[i - 1] == '0') {
      ++ans;
    }
  }
  cout << ans + (b[0] == '1') << '\n';
}