// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  auto Is_prime = [&](int x) {
    if (x < 1) {
      return false;
    }
    for (int i = 2; i * i <= x; ++i) {
      if (x % i == 0) {
        return false;
      }
    }
    return true;
  };


  int ans = -1;
  long long res = -1;
  for (int i = -999; i < 1000; ++i) {
    for (int j = -999; j < 1000; ++j) {
      int cur = 0;
      while (Is_prime(cur * (cur + i) + j)) {
        ++cur;
      }
      if (ans < cur) {
        ans = cur;
        cerr << i << ' ' << j << '\n';
        res = i * j;
      }
    }
  }
  cout << res << '\n';
}