// author: erray
#include<bits/stdc++.h>
 
using namespace std;

#define int long long  
int32_t main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  long long k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  vector<long long> pref(n + 1);
  for (int i = 0; i < n; ++i) {
    pref[i + 1] = pref[i] + a[i];
  }

  const int X = (int) 1e5 + 2;
  vector<int> freq(X);
  for (auto el : a) {
    ++freq[el];
  }

  auto get = [&](int w) {
    int mn = INT_MAX;
    int cnt = 0;
    int p = n;
    long long res = 0;
    long long tot = 0;

    for (int i = 0; i < n; ++i) {
      while (p > 0 && a[p - 1] + a[i] >= w) {
        --p;
      }

      if (p < n && a[p] + a[i] < mn) {
        mn = a[p] + a[i];
        cnt = 0;
      }

      if (p < n && a[p] + a[i] == mn) {
        cnt += freq[a[p]];   
      }

      int c = n - p;
      res += pref.back() - pref[n - c] + 1LL * a[i] * c;
      tot += c;
    }
    if (tot > k && tot - cnt <= k) {
      long long er = tot - k;
      res -= er * mn;
      tot = k;
    }

    return make_pair(tot, res);
  };
  
  int low = 0, high = (int) 3e5;
  while (low < high) {
    int mid = (low + high) >> 1;
    //debug(mid, get(mid));
    auto res = get(mid);
    if (res.first <= k) { 
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  cout << get(low).second << '\n';
}