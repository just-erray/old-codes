// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k, a, b;
  cin >> n >> k >> a >> b;
  --a, --b;
  int cur = a * 2 + b;
  int prev = cur - k, next = cur + k;
  auto range = [&](int w) {
    return w >= 0 && w < n;
  };
  auto convert = [&](int w) {
    return make_pair(w / 2, w % 2);
  };  
  auto print = [&](int w) {
    auto[f, s] = convert(w);
    cout << f + 1 << ' ' << s + 1 << '\n';
    exit(0);
  };
  
  if (range(prev) && range(next)) {
    int prevF = convert(prev).first, nextF = convert(next).first;
    print(a - prevF >= nextF - a ? next : prev);
  } else if (range(next)) {
    print(next);
  } else if (range(prev)) {
    print(prev);
  } else {
    cout << -1 << '\n';
  }
}
