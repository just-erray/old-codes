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
    vector<vector<int>> a(n);
    for (int i = 0; i < n; ++i) {
      int k;
      cin >> k;
      a[i].resize(k);
      for (int j = 0; j < k; ++j) {
        cin >> a[i][j];
        --a[i][j];
      }
    }
    
    map<int, vector<int>> pos;
    for (int i = 0; i < n; ++i) {
      for (auto el : a[i]) {
        pos[el].push_back(i);
      }
    }

  }
}