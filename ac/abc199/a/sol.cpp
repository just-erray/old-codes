// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int a, b, c;
  cin >> a >> b >> c;
  cout << (a * a + b * b < c * c ? "Yes" : "No") << '\n';
}