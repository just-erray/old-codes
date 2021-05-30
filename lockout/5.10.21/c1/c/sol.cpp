// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  string res(n, '*');
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x;
    if (res[x] != '*' && res[x] != y + '0') {
      cout << -1 << '\n';
      return 0;
    }  
    res[x] = y + '0';
  }

  if (res[0] == '0' && n > 1) {
    cout << -1 << '\n';
    return 0;
  }

  for (char& c : res) {
    if (c == '*') {
      c = '0';
    }
  }
  if (n > 1 && res[0] == '0') {
    res[0] = '1';
  }
  cout << res << '\n';
}