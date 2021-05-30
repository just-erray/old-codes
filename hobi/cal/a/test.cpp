// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  auto Solve = [&](int x) {
    set<int> cur;
    for (int i = 0; i < x; ++i) {
      cur.insert(i);
    }
    int now = (x % 2 ? 1 : 0);
    int jump = 2;
    int res = 0;
    while (now != x - 1) {
      now += jump;
      jump += (now >= x);
      now %= x;
      ++res;
    }
    return jump;
  };
  int n;
  cin >> n;
    cout << Solve(n) << '\n';
  for (int i = 1; i < n; ++i) {
  }
}