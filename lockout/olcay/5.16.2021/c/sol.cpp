// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long n;
  cin >> n;
  int sum = 0;
  long long tmp = n;
  vector<int> ct(3);
  int size = 0;
  while (n > 0) {
    sum += n % 10;
    ct[(n % 10 % 3)]++;
    n /=10;
    ++size;
  }
  sum %= 3;
  if (sum % 3 == 0) {
    cout << 0 << '\n';
    return 0;
  }
  if (ct[sum]) {
    if (size == 1) {
      cout << - 1 << '\n';
      return 0;
    }
    cout << 1 << '\n';
  } else {
    if (size == 2) {
      cout << - 1 << '\n';
      return 0;
    }
    cout << 2 << '\n';
  } 
}