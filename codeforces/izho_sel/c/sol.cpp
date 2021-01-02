// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> pos;
  for (int i = 1; i < n; ++i) {
    pos.push_back(a[i] - a[i - 1]);
  }

  sort(pos.begin(), pos.end());
  cout << accumulate(pos.begin(), pos.end() - k + 1, 0LL) + k << '\n';
}