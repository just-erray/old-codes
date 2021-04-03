// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "tavsan";
  freopen((P + ".gir").c_str(), "r", stdin);
  freopen((P + ".cik").c_str(), "w", stdout);
  #endif 
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int x, int y) {
    return a[x] < a[y];
  });
  long long ans = 0;
  set<int> inds;
  inds.insert(-1);
  inds.insert(n);
  for (auto i : ord) {
    auto me = inds.insert(i).first;
    ans = max(ans, 1LL * a[i] * (-*prev(me) + *next(me) - 1)); 
  }
  cout << ans << '\n';
}