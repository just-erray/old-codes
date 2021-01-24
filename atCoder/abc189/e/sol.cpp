// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }

  int m;
  cin >> m;
  struct Piece {
    complex<long long> x{complex<long long>(1, 0)}, y = x;
  };
  vector<int> pref(m + 1);
  vector<Piece> e(m + 1);
  for (int i = 0; i < m; ++i) {
    pref[i + 1] = pref[i];
    Piece cur = e[i];
    int t;
    cin >> t;
    if (t < 3) {
      swap(cur.x, cur.y);
      ++pref[i + 1];
      if (t == 1) {
        cur.y *= -1; 
      } else {
        cur.x *= -1;       
      }
    } else {
      int p;
      cin >> p;
      if (t == 3) {
        cur.x *= -1;
        cur.x.imag(cur.x.imag() + 2 * p);
      } else {
        cur.y *= -1;
        cur.y.imag(cur.y.imag() + 2 * p);
      }
    }
    
    e[i + 1] = cur;
  }

  auto cal = [&](int x, complex<long long> mul) {
    return mul.imag() + mul.real() * x;
  };

  int q;
  cin >> q;
  while (q--) {
    int mm, i;
    cin >> mm >> i;
    --i;
    auto cur = a[i];
    if (pref[mm] % 2) {
      swap(cur.first, cur.second);  
    }
    
    cout << cal(cur.first, e[mm].x) << ' ' << cal(cur.second, e[mm].y) << '\n';
  }
}