// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  vector<char> chart(256);
  chart[0] = ' ';
  int ind = 32;
  set<char> st({'x', 'q', 'w'});
  for (int i = 'a'; i <= 'z'; ++i) {
    if (st.count(i)) {
      continue;
    }
    chart[ind] = i;
    ++ind;
  }
  string s;
  cin >> s;
  string ans;
  for (int i = 0; i < int(s.size()); i += 7) {
    int res = 0;
    for (int j = i; j < i + 7; ++j) {
      res += (s[j] - '0') * (1 << ((i + 6) - j));
    }
    assert(res == 0 || (res >= 32 && res <= 54));
    ans += chart[res];
  }
  cout << ans << '\n';
}