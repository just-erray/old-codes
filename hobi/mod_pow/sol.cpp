// author: erray
#include<bits/stdc++.h>
 
using namespace std;

typedef __int128 int128;
istream& operator>>(istream& in, int128& n) {
  string s;
  in >> s;
  n = 0;
  for (char c : s) {
    n *= 10;
    n += c - '0';
  }
  return in;
}

ostream& operator<<(ostream& out, int128 n) {
  if (n == 0) {
    out << 0;
    return out;
  }
  string res;
  bool neg = n < 0;
  while (n > 0) {
    res += char('0' + n % 10);
    n /= 10;
  }
  if (neg) {
    res += '-';
  }
  reverse(res.begin(), res.end());
  out << res;
  return out;
}
  
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long md;
  int128 a, b;
  cin >> a >> b >> md;
  auto power = [&](int128 x, int128 y) {
    long long res = 1;
    while (y > 0) {
      if (y & 1) {
        res = (int128(res) * x) % md;
      }
      
      x = (int128(x) * x) % md; 
      y >>= 1;
    }

    return res;
  };

  cout << power(a, b) << '\n';
}