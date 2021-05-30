// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int  i = 0; i < n; ++i) {
      cin >> a[i];
    }
    string s;
    cin >> s;
    vector<long long> b(62);
    auto Add_b = [&](long long x, bool query) {
      for (int bit = 0; bit < 62; ++bit) {
        if ((x & (1LL << bit)) == 0) {
          continue;
        }      
        if (b[bit] == 0) {
          if (query) {
            return false;
          }
          b[bit] = x;
          break;
        }
        x ^= b[bit];
      }        
      return true;
    };
    bool win = true;
    for (int i = n - 1; i >= 0; --i) {
      win &= Add_b(a[i], s[i] - '0');
    }

    cout << !win << '\n';
  }
}