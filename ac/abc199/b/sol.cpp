// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int left = 1;
  int right = 1000;
  for (int i = 0; i < n; ++i) {
     int x;
     cin >> x;
     left = max(left, x);
  }

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    right = min(right, x);
  }

  cout << max(0, right - left + 1) << '\n';
}