// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  array<int, vector<int>, 2> a;
  for (int i = 0; i < n; ++i) {
    a[i].resize(n);
    for (int j = 0; j < n; ++j) {
      cin >> a[i][j];
    }
  }
  reverse(a[1].begin(), a[1].end());
  array<int, multiset<int>, 2> st;
  for (int i = 0; i < n; ++i) {
    st[i] = multiset<int>(a[i].begin(), a[i].end());
  }

  
}