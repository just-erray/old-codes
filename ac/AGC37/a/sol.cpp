// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int ans = 0;
  bool bef = true;
  for (int i = 0; i < (int) s.size(); ++i) {
    if (!bef && s[i] == s[i - 1]) {
      ++i;
      if (i == (int) s.size()) {
        --ans;
      }
      bef = true;
    } else {
      bef = false;
    }
    ++ans;
  }
  cout << ans << '\n';
}