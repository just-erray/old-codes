// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = 1; i < n; ++i) {
    if (a[i] == 1) {
      swap(a[i], a[0]);
    }
  }

  for (int i = 0; i < n - 1; ++i) {
    if (a[i] == 2) {
      swap(a[i], a[n - 1]);
    }
  }

  for (auto e : a) {
    cout << e << ' ';
  }
}