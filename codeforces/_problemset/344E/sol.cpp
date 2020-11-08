// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<long long> pref(n + 1), sum(n + 1);
  for (int i = 0; i < n; ++i) {
    sum[i + 1] = sum[i] + a[i];
    pref[i + 1] = pref[i] + (i + 1LL) * a[i];
  }
  vector<long long> dp(n);
  for (int i = n - 1; i >= 0; --i) {
      
  }

  cout << max(pref.back(), *max_element(dp.begin(), dp.end())) << '\n';
}
