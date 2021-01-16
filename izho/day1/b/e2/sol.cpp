//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, x, y;
  cin >> n >> x >> y;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
  }

  y += x;
  vector<long long> ans(n + 1);
  ans[1] = 0;
  for (int i = 2; i <= n; ++i) {
    ans[i] = ans[i - (i / 2)] + ans[(i / 2)] + y;
  }
  
  const int lg = __lg(n) + 3;
  vector<vector<int>> pref(lg, vector<int>(n));
  for (int i = 0; i < lg; ++i) {
    for (int j = 0; j < n - (1 << i); ++j) {
      pref[i][j] = (a[j] != a[j + (1 << i)]);
      if (j > 0) {
        pref[i][j] += pref[i][j - 1];
      }
    }
  }  


  auto get = [&](int ll, int l, int r) {
    if (r < l) {
      return 0;
    }

    return pref[ll][r] - (l == 0 ? 0 : pref[ll][l - 1]);
  };

  auto cal = [&](int l, int r) {
    int sz = r - l + 1;
    int clg = int(__lg(sz - 1));     
    if (sz == 1) {
      return 0;
    }

    if (sz == 2) {
      return 0 + (a[l] == a[r]);
    }
    
    int to = r - (1 << clg) + 1;
    int one = get(clg, l, to - 1);
    int from = l + (1 << clg) - 1 - (1 << (clg - 1));
    int second = get(clg - 1, to, from - 1);
    cerr << to << ' ' << from << ' ' << one << ' ' << second << '\n';
    return one + second;
  };
  
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;   
    --l, --r;
    cerr << cal(l, r) << ' ';
    cout << ans[r - l + 1] + x - 1LL * cal(l, r) * (y) << '\n';
  }
}