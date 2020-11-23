// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long n;
  cin >> n;
  int ans = 0;
  while (n) {
    ++ans;
    n /= 5;
  }
  cout << ans + 1 << '\n';
}