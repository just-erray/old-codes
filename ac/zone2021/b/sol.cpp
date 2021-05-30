// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, D, H;
  cin >> n >> D >> H;
  double ans = 0;
  for (int i = 0; i < n; ++i) {
    int d, h;
    cin >> d >> h;
    int ld = D - d;
    int lh = H - h;
    ans = max(ans,  h - d * 1.0 * lh / ld);
  }
  cout << setprecision(4) << fixed << ans << '\n';
}