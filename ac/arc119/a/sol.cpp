// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long n;
  cin >> n;  
  long long ans = LLONG_MAX;
  for (int i = 0; i < 62; ++i) {
    long long b = 1LL << i;
    long long a = n / b;
    long long c = n % b;
    ans = min(ans, a + i + c);
  }
  cout << ans << '\n';
}