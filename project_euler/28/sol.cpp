// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int cur = 1;
  int add = 2;
  int left = 4;
  long long ans = 0;
  while (cur <= n * n) {
    ans += cur;
    cur += add;
    --left;
    if (left == 0) {
      left = 4;
      add += 2;
    }
  }
  cout << ans << '\n';
}