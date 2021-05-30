// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> p(n);
  iota(p.begin(), p.end(), 0);
  vector<vector<int>> ans;
  do {
    bool ok = true;
    for (int i = 0; i < n - 1; ++i) {
      ok &= (p[i + 1] >= p[i] - 1);
    }
    if (ok) {
      ans.push_back(p);
    }
  } while (next_permutation(p.begin(), p.end()));
  
  cout << (int) ans.size() << '\n';
  for (auto e : ans) {
    for (auto ee : e) {
      cout << ee + 1 << ' ';
    }
    cout << '\n';
  }
}