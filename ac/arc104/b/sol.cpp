// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string s;
  cin >> n >> s;
  string t = "ATGC";
  vector<int> ct(256);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (char c : t) {
      ct[c] = 0;
    }   
    for (int j = i; j >= 0; --j) {
      ++ct[s[j]];
      bool ok = true;
      for (int k = 0; k < 4; k += 2) {
        ok &= (ct[t[k]] == ct[t[k + 1]]);
      }
      ans += ok;
    }
  }
  cout << ans << '\n';
}