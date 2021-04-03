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

    vector<long long> pref(n + 1);
    for (int i = 0; i < n; ++i) {
      pref[i + 1] = pref[i] + a[i];
    }

    long long mx = LLONG_MIN;     
    vector<long long> st;
    map<long long, int> ans;
    for (int i = 1; i <= n; ++i) {
      if (mx > pref[i]) {
        continue;
      }

      mx = pref[i];
      st.push_back(mx);
      ans[mx] = i - 1 ;
    }

    long long ac = accumulate(a.begin(), a.end(), 0LL);
    auto get = [&](long long x) {
      long long tour = x / n;
      long long one = x % n;
      if ((long long) 1e15 / ac <= tour) {
        return LLONG_MAX;
      }

      return tour * ac + pref[one];
    };
    
    const long long inf = (long long) 1e15;
    for (int i = 0; i < m; ++i) {
      long long in;
      cin >> in;
      if (ac > 0) {
        long long low = 1, high = inf;
        while (low < high) {
          long long mid = (low + high) >> 1;
          if (get(mid - 1) >= in) {
            high = mid;
          } else {
            low = mid + 1; 
          }
        }
          w
      } else {
        auto p = lower_bound(st.begin(), st.end(), in);
        if (p == st.end()) {
          cout << -1 << ' ';
        } else {
          cout << ans[*p] << ' ';
        }
      }
    }
    cout << '\n';
  }
}