// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  
  long long ans = 0;       
  array<long long, 2> pref({0, 0});
  for (int i = n - 1; i >= 0; --i) {
    ans = max(ans, pref[i % 2] = a[i] + max(pref[i % 2] - a[i + 1], 0LL));
  }
  cout << ans << '\n';
}