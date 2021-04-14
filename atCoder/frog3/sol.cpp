// author: erray
#include <bits/stdc++.h>
 
using namespace std;
//KACTL line container, true gives max, false gives min
struct Line {
  mutable long long k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(long long x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const long long inf = LLONG_MAX;
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
    if (!is_max) {
      x = -x;
    }
    assert(!empty());
    auto l = *lower_bound(x);
    return -(l.k * x + l.m);
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  long long c;
  cin >> n >> c;
  vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
  }
  LineContainer cht(false);  
  vector<long long> dp(n);
  for (int i = 0; i < n; ++i) {
    long long sq = 1LL * h[i] * h[i];    
    if (i > 0) {
      dp[i] = cht.get(h[i]) + sq + c;
    }
    cht.add(2 * h[i], dp[i] + sq);  
  }
  cout << dp[n - 1] << '\n';
}