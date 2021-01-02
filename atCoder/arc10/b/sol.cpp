// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string s;
  cin >> n >> s;
  if (s[0] == '0') {
    s.insert(s.begin(), 2, '1');
  } 
  if (s[0] == '1' && ((int) s.size() == 1 || s[1] == '0')) {
    s.insert(s.begin(), '1');
  }

  if (s.back() != '0') {
    if (s[(int) s.size() - 2] == '0') {
      s += '1'; 
    }
    s += '0';
  }
  bool ok = ((int) s.size() % 3 == 0);
  for (int i = 0; i < n; i += 3) {
    ok &= s.substr(i, 3) == "110";
  }
  if (!ok) {
    return cout << 0, 0;
  }
  cout << (long long) 1e10 - ((int) s.size()) / 3 + 1;
}