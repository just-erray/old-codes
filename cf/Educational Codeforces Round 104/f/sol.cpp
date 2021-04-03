// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string foo;
  cin >> foo;
  int n = (int) foo.size();
  vector<int> s(n);
  for (int i = 0; i < n; ++i) {
    s[i] = foo[i] - '0';
  }

  int ans = 0;
  int pref = 0;
  for (int i = 0; i < n; ++i) {
    int add = s[i] + pref;
    pref += -add;
    ans += abs(add) * (n - i);
  }

  cout << ans << '\n';

}