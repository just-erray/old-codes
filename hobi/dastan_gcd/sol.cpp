// author: erray
#include<bits/stdc++.h>
 
using namespace std;

using num = array<int, 3>;

istream& operator >>(istream& s, num& x) {
  int a, b, c;
  cin >> a >> b >> c;
  x = {a, b, c};
  return x;
}


num Gcd(num x, num y) {
  num res;
  for (int i = 0; i < 3; ++i) {
    res[i] = min(x[i], y[i]);
  }  

  return res;
}

num

num operator+(num x, num y) {
  num res = Gcd(x, y);
  num av;
  for (int i = 0; i < 3; ++i) {
    x[i] -= mul[i];
    y[i] -= mul[i];
    av[i] = (x[i] + y[i] == 0);
  }  
  
}


 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  num n1, n2, n3;
  cin >> n1 >> n2 >> n3;
  num ans = Gcd(n1 + n2, n3);
  cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << '\n';
}