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
    vector<long long> suf(n + 1);
    int ct = 0;
    for (int i = n - 1; i >= 0; --i) {
      suf[i] = suf[i + 1];
      ct += (s[i] == '*');
      suf[i] += ct * (s[i] == '.');
    }

    long long ans = suf[0];
    long long cur = 0;
    ct = 0;
    for (int i = 0; i < n; ++i) {
      ct += (s[i] == '*');
      cur += ct * (s[i] == '.');
      ans = min(ans, cur + suf[i + 1]);
    }
    cout << ans << '\n';
  }
}