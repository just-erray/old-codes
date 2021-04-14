// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  long long sum = (n / k + !!(n % k)) * k;
  cout << sum / n + !!(sum % n) << '\n';
}