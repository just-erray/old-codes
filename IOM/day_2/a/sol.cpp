#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int x;
  int a, b, c;
  cin >> x >> a >> b >> c;  
  if (min({a, b, c}) == 0) {
    cout << x << ' ' << 0 << '\n';
  } else {
    cout << x - 1 << ' ' << 1 << '\n';
  }
}