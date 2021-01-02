// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T, typename F = function<T(const T&, const T&)>> struct SparseTable {
  int n, lg;
  vector<vector<T>> table;
  F cal;

  SparseTable(vector<T> v, F _cal) : n((int) v.size()), cal(_cal) {
    lg = 32 - __builtin_clz(n);
    table.resize(lg);
    table[0] = v;
    for (int i = 1; i < lg; ++i) {
      table[i].resize(n - (1 << i) + 1);
      for (int j = 0; j < (int) table[i].size(); ++j) {
        table[i][j] = cal(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  T get(int l, int r) {
    assert(l >= 0 && r < n && l >= r);
    int clg = 31 - __builtin_clz(r - l + 1);
    return cal(table[clg][l], table[clg][r - (1 << clg) + 1]);
  }
};

 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}