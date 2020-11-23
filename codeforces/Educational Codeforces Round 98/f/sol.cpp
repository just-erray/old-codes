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
    int t, p;
    long long x;
    cin >> t >> p >> x;
    if (t == 1) {
      a[p] = int(x);
      continue;
    }
    
    long long ans = 0;
    auto need = [&](long long now, int i) {
      int f = p - i + 1;
      
    };

    for (int i = 0; i < n; ++i) {
      if (i < p) {
        x -= min(x, a[i]);
        continue;
      }  
      int f = p - i + 1;
      if ((1LL << f) * a[i] >= x) {
        need(a[i], i);
        break;  
      } 
    }
    cout << (x ? ans : -1) << '\n';
  }
}