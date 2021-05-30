// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  n += 5;
  vector<int> ct(2);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    ++ct[x % 2];
  }
  cout << (ct[1] > 0 && ct[0] > 0) << '\n';
}