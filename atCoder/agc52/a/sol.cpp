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
    vector<string> s(3);
    cin >> s[0] >> s[1] >> s[2];
    auto f = [&](char c) {
      set<int> st;
      vector<int> p(3);
      int res = -1;
      for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < 3; ++j) {
          if (s[j][i] == c) {
            if (i == 0 || s[j][i - 1] != c) {
              if (st.insert(p[j]).second) {
                res = p[j];
              }
            }
          } else {
            ++p[j];  
          }
        }
      }
      return res;
    };
    string ans = string(2 * n, '0');
    int p = f('1');
    assert(p != -1);

  }
}