// author: erray
#include <bits/stdc++.h>
 
using namespace std;

constexpr int M = 3;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  array<int, M> size;
  for (int i = 0; i < M; ++i) {
    cin >> size[i];
  }
  int n = accumulate(size.begin(), size.end(), 0);
  vector<array<int, M>> a(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < M; ++j) {
      cin >> a[i][j];
    }
  }
  // M = 2
  // take left
  // greedy right
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    ans += a[i][0];
    for (int j = 1; j < M; ++j) {
      a[i][j] -= a[i][0];
    }
  }

  for (int i = 0; i < n; ++i) {
    
  }


}