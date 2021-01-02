// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  set<pair<int, int>> s;
  while (n--) {
    int x, y;
    cin >> x >> y;
    if (x) {
      int g = gcd(x, y);
      x /= g;
      y /= g;
      if (x < 0) {
        x = -x;
        y = -y;
      }
      s.emplace(x, y);
    }   
  }
  cout << (int) s.size() << '\n';
}