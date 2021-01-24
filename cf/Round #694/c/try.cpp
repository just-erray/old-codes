// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k, t;
  cin >> n >> k >> t;
  vector<int> a(n, k);
  for (int i = 0; i < n * 3; ++i) {
    vector<int> new_a(n);
    for (int j = 0; j < n; ++j) {
      int l = a[j] / 2;
      int r = a[j] - l;
      if (t == j) {
        new_a[(j + 1) % n] += a[j];
      } else {
        new_a[(j - 1 + n) % n] += l;
        new_a[(j + 1) % n] += r;
      }
    }

    swap(a, new_a);
    for (int j = 0; j < n; ++j) {
      cout << a[j] << ' ';
    }
    cout << '\n';
  }
}