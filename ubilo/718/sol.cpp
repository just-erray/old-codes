// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "donusum";
  freopen((P + ".gir").c_str(), "r", stdin);
  freopen((P + ".cik").c_str(), "w", stdout);
  #endif 
  string s, t;
  cin >> s >> t;
  int n = (int) s.size();
  int m = (int) t.size();

  vector<array<int, 2>> prefs(n + 1);
  for (int i = 0; i < n; ++i) {
    prefs[i + 1] = prefs[i];
    ++prefs[i + 1][s[i] == 'A'];
  }

  vector<array<int, 2>> preft(m + 1);
  for (int i = 0; i < m; ++i) {
    preft[i + 1] = preft[i];
    ++preft[i + 1][t[i] == 'A'];
  }

  int q;
  cin >> q;
  while (q--) {
    int ls, rs, lt, rt;
    cin >> ls >> rs >> lt >> rt;
    --ls, --lt;
    array<int, 2> from = prefs[rs];
    from[0] -= prefs[ls][0];
    from[1] -= prefs[ls][1];

    array<int, 2> to = preft[rt];
    to[0] -= preft[lt][0];
    to[1] -= preft[lt][1];
    cout << ((-(to[0] - from[0]) + to[1] - from[1]) % 3 == 0 ? "YES" : "NO") << '\n'; 
  }
}