//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, s, t;
  cin >> n >> s >> t;
  --s, --t;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  
  if (s < t) {
    long long cost = 0;
    long long ans = LLONG_MAX;
    for (int i = s; i >= 0; --i) {
      ans = min(ans, cost + 1LL * (t - i) * a[i]);
      cost += a[i];
    }
    cout << ans << '\n';

  } else {
    long long ans = 0;
    for (int i = s - 1; i >= t; --i) {
      ans += a[i + 1]; 
    }    
    cout << ans << '\n';
  }

}