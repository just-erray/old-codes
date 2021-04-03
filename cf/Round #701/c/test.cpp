// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  for (int x = 2; x <= n; ++x) {
    auto Get = [&x](int y) {
      int t = min(1LL * x, 1LL * y * (y - 1) + y - 1);
      int low = 0, high = y - 1;
      while (low < high) {
        int mid = 1 + ((low + high) >> 1);
        if (1LL * mid * y + mid <= x) {
          low = mid;
        } else {
          high = mid - 1;
        }
      } 

      return low;
    };
    
    int mx = -1;
    for (int j = 1; j <= x; ++j) {
      mx = max(Get(j), mx);
    }

    if (mx > Get(ceil(sqrt(x))) && mx > Get(sqrt(x))) {
      cerr << x << '\n';
    }
  }
}