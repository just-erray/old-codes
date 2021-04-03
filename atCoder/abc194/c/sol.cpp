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
  long long ans = 0;
  const int N = 401;
  vector<int> ct(N);
  for (int i = 0; i < n; ++i) {
    ++ct[a[i] + 200];
    for (int j = 0; j < N; ++j) {
      ans += 1LL * ct[j] * (a[i] - (j - 200)) * (a[i] - (j - 200));
    }
  }
  cout << ans << '\n';
}