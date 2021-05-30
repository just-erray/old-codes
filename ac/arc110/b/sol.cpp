// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string s;
  cin >> n >> s;
  string c = "110";
  auto Can = [&](int x) {
    bool ok = true;
    for (int i = 0; i < n - x; ++i) {
      ok &= (s[x + i] == c[i % 3]); 
    }
    return ok;
  };

  long long ans = 0;
  for (int i = 0; i < min(3, n); ++i) {
    ans += Can(i) * ((long long) 1e10 - n / 3);
  }
  cout << ans << '\n';
}