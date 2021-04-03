// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }

  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int x, int y) {
    return a[x] < a[y];
  });

  bool ok = true;
  int lst = (int) -2e5;
  for (auto i : ord) {
    ok &= (lst < a[i] - b[i] + 1);
    lst = a[i];
  }

  cout << (ok ? "YES" : "NO") << '\n';
}
