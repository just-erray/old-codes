// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    a.erase(unique(a.begin(), a.end()), a.end());
    if (k == 1 && (int) a.size() > 1 && a[0] == 0) {
      cout << -1 << '\n';
      continue;
    }
    cout << (int) ceil((double) a.size() / k) << '\n';
  }
}