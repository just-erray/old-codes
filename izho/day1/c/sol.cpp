//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, foo;
  cin >> n >> foo;
  vector<int> a(n), t(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = 0; i < n; ++i) {
    cin >> t[i];
  }

  if ((is_sorted(a.begin(), a.end()) || is_sorted(a.rbegin(), a.rend())) && a != t) {
    return cout << "NO\n", 0;
  }
  cout << "YES\n";
} 