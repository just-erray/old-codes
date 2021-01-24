// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long a, b;
  cin >> a >> b;
  long long ans = 0;

  while (b != 0) {
    if (a > b) {
      swap(a, b);
    }
    ans += (b / a);
    b %= a;
  }
  cout << ans << '\n';
}