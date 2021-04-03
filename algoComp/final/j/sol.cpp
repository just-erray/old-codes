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
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      --a[i];
    }

    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
      cin >> b[i];
      --b[i];
    }

    vector<vector<int>> posA(3);
    for (int i = 0; i < n; ++i) {
      posA[a[i]].push_back(i);
    }

    vector<vector<int>> posB(3);
    for (int i = 0; i < m; ++i) {
      posB[b[i]].push_back(i);
    }

    auto nextA = [&](int x, int want = 0) {
      if (want != 2) {
        if (posA[want].empty() || x >= posA[want].back()) {
          return m;  
        }

        return *lower_bound(posA[want].begin(), posA[want].end(), x + 1);
      } else {        
        if (posA[want].empty() || x <= posA[want][0]) {
          return m;  
        }

        return *prev(lower_bound(posA[want].begin(), posA[want].end(), x));
      }
    };
    
    auto nextB = [&](int x, int want = 0) {
      if (want != 2) {
        if (posB[want].empty() || x >= posB[want].back()) {
          return m;  
        }

        return *lower_bound(posB[want].begin(), posB[want].end(), x + 1);
      } else {        
        if (posB[want].empty() || x <= posB[want][0]) {
          return m;  
        }

        return *prev(lower_bound(posB[want].begin(), posB[want].end(), x));
      }
    };

    vector<tuple<int, int, int>> pairs;
    int indA = -1, indB = -1;
    int addc = 0;
    while (indA < n && indB < m) {
      pairs.emplace_back(indA, indB, addc);
      indA = nextA(indA);
      indB = nextB(indB);
      ++addc;
    }

    const int size = (int) pairs.size();
    vector<pair<int, int>> dp;
    for (int i = 0; i < size - 1; ++i) {
      
    }

  }
}