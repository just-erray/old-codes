// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "sabotage";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n;
  cin >> n;
  vector<double> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  auto get = [&](double m, vector<double> x) {
    long double tot = 0;
    for (auto& e : x) {
      e -= m;
      tot += e;
    }    

    long double mn = x[0];
    long double sum = x[0];
    long double res = -1e4;

    for (int i = 1; i < n - 1; ++i) {
      sum += x[i];
      res = max(res, sum - mn);
      mn = min(mn, sum);
    }

    return ((tot - res) <= 0);
  };
  
  double low = 0, high = 1e4;
  int bs_ct = 100;
  while (bs_ct--) {
    double mid = (low + high) * 0.5;
    if (get(mid, a)) {
      high = mid;
    } else {
      low = mid;
    }
  }

  cout << setprecision(3) << fixed << low << '\n';
}