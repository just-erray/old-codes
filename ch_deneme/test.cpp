// author: erray
#include <bits/stdc++.h>
 
using namespace std;

//KACTL line container, true finds max, false finds min point
struct Line {
  mutable long long k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(long long x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const long long inf = (long long) 1e18;
  bool is_max = true;
  LineContainer(bool _is_max = true) : is_max(_is_max) { }
  long long div(long long a, long long b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(long long k, long long m) {
    if (!is_max) {
      k = -k;
      m = -m;
    }
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  long long get(long long x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return (l.k * x + l.m) * (is_max ? 1 : -1);
  }
};
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long n;
  cin >> n;
  LineContainer lc;
  for (long long i = 0; i < n; ++i) {
    long long x, y;
    cin >> x >> y;
    lc.add(x, y);
  }
  for (long long i = 0; i < n; ++i) {
    long long x;
    cin >> x;
    cout << lc.get(x) << '\n';
  }
  
}