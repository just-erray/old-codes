// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  string s;
  --m;
  vector<int> fact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fact[i] = fact[i - 1] * i;
  }
  vector<int> pass;

  for (int j = n - 1; j >= 0; --j) {
    pass.push_back(0);
    while (m >= fact[j]) {
      ++pass.back();
      m -= fact[j];
    }
  }
  vector<int> left(n);
  iota(left.begin(), left.end(), 0);
  string ans;

  for (int i = 0; i < n; ++i) {
    ans += char('0' + left[pass[i]]);
    left.erase(left.begin() + pass[i]);      
  }
  cout << ans << '\n';
}