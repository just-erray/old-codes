// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  /*
  int ind = 0;
  while (ind < (int) s.size() && s[ind] == 'F') {
    ++ind;
  }
  s.erase(s.begin(), s.begin() + ind);
  
  ind = (int) s.size() - 1;
  while (ind >= 0 && s[ind] == 'M') {
    --ind;
  }
  s.erase(s.end() - ind, s.end());
  */
  const int n = (int) s.size();
  int cur = 0, ans = 0;
  for (char c : s) {
    if (c == 'M') {
      ++cur;
    } else {
      ans = max(ans + bool(ans), cur);
    }
  }
  cerr << ans << '\n';
  cur = 0;
  int ans2 = 0;
  reverse(s.begin(), s.end());
  for (char c : s) {
    if (c == 'F') {
      ++cur;
    } else {
      ans2 = max(ans2 + bool(ans2), cur);
    }
  }

  cout << max(ans, ans2) << '\n';
}