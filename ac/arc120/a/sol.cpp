// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<long long> pref(n + 1);
  for (int i = 0; i < n; ++i) {
    pref[i + 1] = pref[i] + a[i];
  }

  int mx = 0;
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    mx = max(mx, a[i]);
    sum += pref[i + 1];
    cout << sum + 1LL * mx * (i + 1) << '\n';
  }
}