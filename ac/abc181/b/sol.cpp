// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  long long ans = 0;
  auto Gauss = [&](int x) {
    return 1LL * x * (x + 1) / 2;
  };
  while (n--) {
    int a, b;
    cin >> a >> b;
    ans += Gauss(b) - Gauss(a - 1);
  }
  cout << ans << '\n';
}