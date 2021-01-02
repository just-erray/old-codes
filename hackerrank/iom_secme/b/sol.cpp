// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  const int n = 12;
  vector<bool> active(n, true);
  vector<vector<vector<int>>> st;
  for (int i = 0; i < 3; ++i) {
    vector<vector<int>> p(2, vector<int>(4));
    char c;
    for (int q = 0; q < 2; ++q) {
      for (int j = 0; j < 4; ++j) {
        cin >> p[q][j];
        --p[q][j];
      }
      if (!q) cin >> c;
    }
    if (c == '=') {
      for (auto e : p) {
        for (auto el : e) {
          active[el] = false;
        }
      }
      continue;
    }
    if (c == '>') {
      swap(p[0], p[1]);
    }
    st.push_back(p);
  }

  auto solve = [&] {
    vector<bool> act = active;
    vector<bool> act2(n, true);
    for (auto el : st) {
      for (auto e : el[1]) {
        act[e] = false;
      }
      vector<bool> tmp(n, false);
      for (auto e : el[0]) {
        tmp[e] = true;
      }
      for (int i = 0; i < n; ++i) {
        if (!tmp[i]) {
          act2[i] = false;
        }
      }
    }
    int res = -1;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (act[i] && act2[i]) {
        res = i;
        ++cnt;
      }
    }
    if (cnt == 0) {
      return 12;
    }

    if (cnt > 1) {
      return -1;
    }

    return res;
  };

  int f = solve();
  for (auto& el : st) {
    swap(el[0], el[1]);
  }
  int s = solve();

  if (f != n && f != -1 && (s == -1 || s == n)) {
    cout << f + 1 << '-' << '\n';
  } else if (s != n && s != -1 && (f == -1 || f == n)) {
    cout << s + 1 << '+' << '\n';
  } else if ((f != n && f != -1 && s != -1 && s != n) ||  f == -1 || s == -1) {
    cout << "indefinite";
  } else {
    cout << "impossible";
  }


}