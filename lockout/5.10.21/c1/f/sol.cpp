// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<array<int, 3>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i][0] >> a[i][1] >> a[i][2];
  }

  
  auto sq = [&](int x) {
    return 1LL * x * x;
  };

  auto Dist = [&](int x, int y, int x2, int y2) {
    return sqrt(sq(x - x2) * sq(y - y2));
  };
  auto Pos = [&](long double x) {
     
  };
  
  long double low = 0, high = 1e6;
  int bs_it = 200;
  while (bs_it--) {
    long double mid = (low + high) / 2;
    if (Pos(mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }
}