// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  const int MAX = int(1e6 + 1);
  vector<int> vis(MAX);
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    vis[a[i]]++;
  }

  bool ok = true;
  for (int i = 2; i < MAX; ++i) {
    int ct = 0;
    for (int j = i; j < MAX; j += i) {
      ct += vis[j];
    }  
    ok &= (ct <= 1);
  }
  int d = 0;
  for (int i = 0; i < n; ++i) {
    d = gcd(d, a[i]);
  }
  if (ok) {
    cout << "pairwise coprime" << '\n';
  } else if (d == 1) {
    cout << "setwise coprime" << '\n';
  } else {
    cout << "not coprime" << '\n';
  }
}