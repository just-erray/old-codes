// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      int f = i * i - j * j;
      int s = (int) sqrt(f);
      if (s * s == f && i == s * s - j) {
        cout << i << ' ' << j << ' ' << s << '\n';
      } 
    }
  }
}