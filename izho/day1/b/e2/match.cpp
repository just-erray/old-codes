//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> ans(n, -1);
  function<void(vector<int>, int)> f = [&](vector<int> a, int d = 0) {
    if ((int) a.size() == 1) {
      return;
    }  
    
    if ((int) a.size() == 2) {
      ans[a[0]] = a[1];
      ans[a[1]] = a[0];
      return;
    }  
    vector<int> left, right;
    for (auto e : a) {
      cerr << e << ' ';
      if ((e >> d) & 1) {
        right.push_back(e);
      } else {
        left.push_back(e);
      }
    }

    cerr << '\n';
    f(left, d + 1);
    f(right, d + 1);
  };
  vector<int> foo(n);
  iota(foo.begin(), foo.end(), 0);
  f(foo, 0);

  for (auto e : ans) {
    cout << e << ' ';
  }
}