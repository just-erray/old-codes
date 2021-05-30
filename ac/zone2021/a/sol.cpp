// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  string t = "ZONe";
  int ans = 0;
  for (int i = 0; i < int(s.size()) - 3; ++i) {
    bool ok = true;
    for (int j = 0; j < 4; ++j) {
      ok &= (s[i + j] == t[j]);
    }
    ans += ok;
  }
  cout << ans << '\n';
}