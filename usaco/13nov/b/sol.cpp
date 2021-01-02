// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "sight";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, r;
  cin >> n >> r;
  vector<array<int, 2>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i][0] >> a[i][1];
  }
  

}
