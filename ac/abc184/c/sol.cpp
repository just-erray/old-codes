// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, t;
  cin >> n >> t;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  auto Comb = [&](int l, int r) {
    vector<int> av = {0};
    int size = r - l + 1;
    for (int mask = 0; mask < (1 << size); ++mask) {
      long long sum = 0;
      for (int i = 0; i < size; ++i) {
        if ((mask >> i) & 1) {
          sum += a[l + i];
        }
      }
      if (sum <= t) {
        av.push_back(sum);
      }
    }
    sort(av.begin(), av.end());
    av.erase(unique(av.begin(), av.end()), av.end());
    return av;
  };
  int ans = 0;
  int dv = n / 2;
  vector<int> left = Comb(0, dv);
  vector<int> right = Comb(dv + 1, n - 1);
  for (auto e : left) {
    if (e > t) {
      continue;
    }
    int ot = *prev(lower_bound(right.begin(), right.end(), t - e + 1));
    ans = max(ans, e + ot);
  }
  cout << ans << '\n';
}