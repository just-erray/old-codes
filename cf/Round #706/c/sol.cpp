// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<string> mat(n);
    for (int i = 0; i < n; ++i) {
      cin >> mat[i];
    }
    for (int i = 0; i < n; ++i) {
      if (i % 3 == 0) {
        mat[i] = string(m, '#');
      }
    }
  }
}