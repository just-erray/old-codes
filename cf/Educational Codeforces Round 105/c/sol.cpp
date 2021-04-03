// author: erray
#include<bits/stdc++.h>
 
using namespace std;

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }

    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
      cin >> b[i];
    }

    auto solve = [](auto x, auto y) {
      if (x.empty() || y.empty()) {
        return 0;
      }

      if (x[0] < 0) {
        reverse(x.begin(), x.end());
        reverse(y.begin(), y.end());
        for (auto& e : x) {
          e *= -1;
        }
        
        for (auto& e : y) {
          e *= -1;
        }
      }

      debug(x, y);
      
      int n = (int) y.size();
      int m = (int) x.size();
      vector<int> ct(m + 1);
      for (int i = m - 1; i >= 0; --i) {
        ct[i] = ct[i + 1] + binary_search(y.begin(), y.end(), x[i]);
      }

      debug(ct);

      for (int i = 0; i < m; ++i) {
        int res = 0;
        int from = int(lower_bound(y.begin(), y.end(), x[i]) - y.begin());
        while (from < n && (i == m - 1 || y[from] < x[i + 1])) { 
          debug(from);
          int to = from - int(lower_bound(y.begin(), y.end(), y[from] - i) - y.begin()) + 1;
          res = max(res, to); 
          ++from;
        }
        ct[i + 1] += res;
      }

      debug(ct);
      return *max_element(ct.begin(), ct.end());
    };
    
    auto pa = lower_bound(a.begin(), a.end(), 0);
    auto pb = lower_bound(b.begin(), b.end(), 0);
    cout << solve(vector<int>(a.begin(), pa), vector<int>(b.begin(), pb)) + solve(vector<int>(pa, a.end()), vector<int>(pb, b.end())) << '\n';
  }
}