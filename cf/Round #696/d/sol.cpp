// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }

    auto peak = [&] {
      int start = 0;
      while (start < n - 1 && a[start] <= a[start + 1]) {
        ++start;
      }

      int end = n - 1;
      while (end > 0 && a[end] <= a[end - 1]) {
        --end;
      }

      return make_pair(start, end);
    };

    auto solve = [&] {
      vector<int> tmp = a;
      
    };
  }
}