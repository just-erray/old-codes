// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    string s;
    cin >> n >> s;
    vector<bool> vis(256);
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      ok &= (!vis[s[i]] || s[i] == s[i - 1]);
      vis[s[i]] = true; 
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}