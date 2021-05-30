// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> add(256);
  cin >> add['s'] >> add['p'] >> add['r'];
  string s;
  cin >> s;
  vector<int> lst(k, -1);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int me = i % k;
    if (lst[me] != s[i]) {
      lst[me] = s[i];
      ans += add[s[i]];
    } else {
      lst[me] = -1;
    }
  }
  cout << ans << '\n';
}