// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<array<int, 2>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i][0] >> a[i][1];
  }
  sort(a.begin(), a.end());
  
}