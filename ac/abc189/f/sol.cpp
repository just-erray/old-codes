// author: erray
#include<bits/stdc++.h>
 
using namespace std;

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(k);
  for (int i = 0; i < k; ++i) {
    cin >> a[i];
  }
  
  const int N = n + max(n, m) + 2;
  vector<complex<long double>> dp(N);
  vector<bool> mark(n);
  complex<long double> cur;
  int lst = -1;
  int sz = 0;
  for (auto e : a) {
    dp[e] = complex<long double>(1, 0);
    mark[e] = true;
    if (lst == e - 1) {
      ++sz;
    } else {
      sz = 1;
    }
    
    lst = e;
    if (sz >= m) {
      cout << -1 << '\n';
      return 0;
    }
  }

  for (int i = n - 1; i >= 0; --i) {
    cur -= dp[i + m + 1];
    if (!mark[i]) {
      dp[i] = cur / (long double) m;
      dp[i].imag(dp[i].imag() + 1);
    }

    cur += dp[i];
  }



  cout << setprecision(4) << fixed << dp[0].imag() / ((long double) 1 - dp[0].real()) << '\n';
}                                