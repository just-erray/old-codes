// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int ans = 0;
  string t = "eren";
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    int p = 0;
    for (int j = 0; j < int(s.size()); ++j) {
      if (t[p] == s[j]) {
        ++p;
      }
      if (p == 4) {
        break;
      }
    }
    ans += (p == 4);
  }
  cout << ans << '\n';
}