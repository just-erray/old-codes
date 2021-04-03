// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int n = (int) s.size();
  int k = count(s.begin(), s.end(), 'K');
  int cur = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    cur += (s[i] == 'K');
    if (i >= k) {
      cur -= (s[i - k] == 'K');
    }
    ans = max(ans, cur);
  }
  cout << k - ans << '\n';
}