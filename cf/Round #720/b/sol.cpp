// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
     
    vector<array<int, 4>> ans;
    int pos = min_element(a.begin(), a.end()) - a.begin();
    int mn = *min_element(a.begin(), a.end());
    if (pos > 0) {
      ans.push_back({0, pos, mn, int(2e9)});
    }

    for (int i = 1; i < n; ++i) {
      ans.push_back({0, i, mn, mn + i});
    }

    cout << int(ans.size()) << '\n';
    for (auto[i, j, x, y] : ans) {
      cout << i + 1 << ' ' << j + 1 << ' ' << x << ' ' << y << '\n';
    }
  }
}