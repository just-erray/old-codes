// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  map<int, int> need;
  map<int, bool> al_t;
  multiset<int> ms; 
  int big = -1;
  int al = 0;
  for (int i = 0; i < n; ++i) {
    auto me = ms.lower_bound(a[i]);
    if (big >= a[i]) {   
      if (me == prev(ms.end())) {
        need[big]++;
      }
    } else {
      ++al;
      al_t[a[i]] = true;
    }
    ms.insert(a[i]);
    big = max(big, a[i]);
  }

  if (need.empty()) {
    cout << al - 1 << '\n';
    return 0;
  }
  int ans = 0;
  for (auto[x, w] : need) {
    ans = max(ans, w + al - al_t[x]);
  }
  cout << ans << '\n';
}