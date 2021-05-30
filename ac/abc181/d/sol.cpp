// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int n = int(s.size());
  if (n == 1) {
    cout << ((s[0] - '0') % 8 == 0 ? "Yes" : "No") << '\n';
    return 0;
  } else if (n == 2) {
    int b0 = s[0] - '0';
    int b1 = s[1] - '0';
    if ((b0 * 10 + b1) % 8 == 0 || ((b1 * 10 + b0) % 8 == 0)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
    return 0;
  }
  vector<int> ct(10);
  for (char c : s) {
    ct[c - '0']++;
  }
  bool ok = false;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      for (int k = 0; k < 10; ++k) {
        vector<int> cur(10);
        ++cur[i];
        ++cur[j];
        ++cur[k];
        bool no = false;
        for (int q = 0; q < 10; ++q) {
          if (cur[q] > ct[q]) {
            no = true;
          }
        }
        if (!no) {
          int cur = i * 100 + j * 10 + k;
          if (cur % 8 == 0) {
            ok = true;
          }
        }
      }
    }
  }
  cout << (ok ? "Yes" : "No") << '\n';
}