// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long x;
  cin >> x;
  while (x) {
    long long a, b;
    a = b = 1;
    bitset<64> bs(x);
    int ind = 63;
    while (!bs[ind]) {
      --ind;
    }
    --ind;
    while (ind >= 0) {
      if (bs[ind] & 1) {
        a = (a + b);
      } else {
        b = (b + a);
      } 
      --ind;
    }
    cout << a << '/' << b << '\n';
    cin >> x;
  }
}