// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int a, b, k;
  cin >> a >> b >> k;
  if (k == 0) {
    cout << "Yes\n";
    cout << string(b, '1');
    cout << string(a, '0') << '\n';
    cout << string(b, '1');
    cout << string(a, '0') << '\n';
    return 0;
  }

  if (b == 1 || a == 0 || a + b == k) {
    cout << "No\n";
    return 0;
  }

  string y = "10";
  y += string(b - 1, '1');
  y += string(a - 1, '0');
  int del = k - 1;
  string x = y;
  for (int i = 0; i < n; ++i) {
    
  }


}