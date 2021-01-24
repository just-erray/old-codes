// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T, typename F = function<T(const T&, const T&)>> class SparseTable {
  public:
  int sz, lg;
  vector<vector<T>> table;
  F cal;
  SparseTable() { }
  SparseTable(vector<T> v, F _cal) : cal(_cal) {
    sz = (int) v.size();
    lg = 32 - __builtin_clz(sz);
    table.resize(lg);
    table[0] = v;
    for (int i = 1; i < lg; ++i) {
      table[i].resize(sz - (1 << i) + 1);
      assert(sz - (1 << i) + 1 >= 0);
      for (int j = 0; j < (int) table[i].size(); ++j) {
        table[i][j] = cal(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  T get(int l, int r) {
    assert(l >= 0 && r < sz && l <= r);
    int clg = 31 - __builtin_clz(r - l + 1);
    return cal(table[clg][l], table[clg][r - (1 << clg) + 1]);
  }
};

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  string s;
  cin >> n >> q >> s;

  auto solve = [&] {
    vector<char> foo(s.begin(), s.end());
    SparseTable<char> st(foo, [&](char x, char y) {
      return min(x, y);
    });
    
    vector<int> res(n + 1);
    vector<int> lst(256, -1);

    for (int i = 0; i < n; ++i) {
      char add = s[i];
      res[i + 1] = res[i];
      if (lst[add] == -1 || st.get(lst[add], i) < add) {
        ++res[i + 1];
      }

      lst[add] = i;
    }
    
    return res;
  };

  auto pref = solve();
  reverse(s.begin(), s.end());
  auto suf = solve();

  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << pref[l - 1] + suf[n - r] << '\n';
  }
}