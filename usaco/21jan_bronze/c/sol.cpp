// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  long long ans = 1;
  for (int i = 0; i < n; ++i) {
    ans *= max(0, (int(lower_bound(a.begin(), a.end(), b[i] + 1) - a.begin()) - i));
  }

  cout << ans << '\n';
}