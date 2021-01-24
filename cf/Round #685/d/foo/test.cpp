// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int res = 0;
  for (int i = 0; i < n; ++i) {
    res += (int) ceil(sqrt((long double) n * n - ((i + 1) * (i + 1))));
  }
  cout << res << '\n';
}