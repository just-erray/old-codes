// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long n;
  cin >> n;
  long long three = 1;
  for (int i = 0; i < n; ++i) {
    three *= 3;
    if (three > n) {
      break;
    }
    long long five = 5;
    int j = 0;
    while (five + three < n) {
      five *= 5;
      ++j;
    }
    if (five + three == n) {
      cout << i + 1 << ' ' << j + 1 << '\n';
      return 0;
    }
  }

  cout << - 1 << '\n';
}