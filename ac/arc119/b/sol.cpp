// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string s, t;
  cin >> n >> s >> t;
  if (count(s.begin(), s.end(), '1') != count(t.begin(), t.end(), '1')) {
    cout << -1 << '\n';
    return 0;
  }
  int ans = 0;
  for (int 
}