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
  
  if (s > t) {
    s = n - s - 1;
    t = n - t - 1;
    reverse(a.begin(), a.end());
  }
  
  vector<int> lbig, rbig, lsmall, rsmall;

}