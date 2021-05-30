// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long n;
  cin >> n;
  long long ans = n / 2;
  int jump = 3;
  long long cur = 0;
  while (cur != n - 1) {
    if (cur % jump == (n - 1) % jump) {
      ans += (n - 1 - cur) / jump;      
      cur = n - 1;
    } else {
      long long left = n - cur;
      long long go = left / jump + !!(left % jump);
      ans += go;
      cur += go * jump;
      cur %= n;
    }
    ++jump;
  }
  cout << ans << '\n';
}