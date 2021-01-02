// author: erray
#include<bits/stdc++.h>
 
using namespace std;
#define int long long
 
int32_t main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int x, y;
  cin >> x >> y;
  auto print = [](int a) {
    cout << a << '\n';
    exit(0);
  };
  
  if (x == y) {
    print(0);
  }

  auto pos = [&](bool b, int val) {
    if (!b) {
      return LLONG_MAX;
    }  
    return val;
  };

  if (y > x) {
    print(min((y - x), pos(x <= 0 && y >= 0, 1 + abs(-x - y))));
  } else {
    if (x < 0) {
      print(2 + x - y);
    } else {
      if (y < 0) {
        print(1 + abs(x - abs(y)));
      } else {
        print(min(y + x + 1, 2 + x - y));
      }
    }
  }
}