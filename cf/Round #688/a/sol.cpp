// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    long long ans = 0, cur = 0;
    for (auto el : a) {
      long long add = a[0] - (el + cur);
      ans += abs(add);
      cur += add;
    }
    cout << ans << '\n';
  }
}