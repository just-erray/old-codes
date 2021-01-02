// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int pos, val;
      cin >> pos >> val;
      a[pos - 1] = val;
      continue;
    } 
    int x;
    long long k;
    cin >> x >> k;

  }
}