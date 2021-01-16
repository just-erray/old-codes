//author: erray
#include <bits/stdc++.h>

using namespace std;

struct SparseTable {
  int n;
  int lg;
  vector<vector<int>> table;
  SparseTable(vector<int> a) {
    n = (int) a.size();
    lg = 32 - __builtin_clz(n);
    table.resize(lg);
    table[0] = a;
    for (int i = 1; i < lg; ++i) {
      table[i].resize(n - (1 << i) + 1);
      for (int j = 0; j < (int) table[i].size(); ++j) {
        table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  int get(int l, int r) {
    assert(l >= 0 && r < n && l <= r);
    int b = 31 - __builtin_clz(r - l + 1);
    return min(table[b][l], table[b][r - (1 << b) + 1]);   
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, s, t;
  cin >> n >> s >> t;
  --s, --t;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  
  if (s > t) {
    s = n - s - 1;
    t = n - t - 1;
    reverse(a.begin(), a.end());
  }
  SparseTable st(a);
  
  auto find_first = [&](int x) {
    int low = x, high = t;
    while (low < high) {
      int mid = (low + high) >> 1;
      if (st.get(x, mid) > a[x]) {
        high = mid;    
      } else {
        low = mid + 1;
      }
    }

    return low;
  };

  vector<int> dp(n);
  
}