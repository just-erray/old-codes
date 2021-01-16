#include<bits/stdc++.h>

using namespace std;

#define int int64_t

template<typename T> void debug(vector<T> v) {
  #ifdef LOCAL
  cerr << "{";
  for (auto e : v) {
    cerr << e << ' ';
  }
  cerr << '}' << endl;
  #endif
}

struct SparseTable {    
  vector<vector<long long>> table;
  int n;
  int lg;
  SparseTable(vector<long long> a) {
    n = (int) a.size();
    lg = 32 - __builtin_clz(n);
    table.resize(lg);
    table[0] = a;
    for (int j = 1; j < lg; ++j) {
      table[j].resize(n + 1 - (1 << j));
      for (int i = 0; i < (int) table[j].size(); ++i) {
        table[j][i] = max(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  long long get(int l, int r) {
    assert(l >= 0 && r < n && r >= l);
    int L = 31 - __builtin_clz(r - l + 1);
    return min(table[L][l], table[L][r + 1 - (1 << L)]);
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n), b(n + 1);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = 0; i <= n; ++i) {
    cin >> b[i];
  }

  auto solve = [&] {
    vector<long long> pref(n + 1);
    for (int i = 0; i < n; ++i) {
      pref[i + 1] = pref[i] + a[i];
    }
    
    vector<long long> sc(n + 1);
    for (int i = 0; i <= n; ++i) {
      sc[i] = b[i] - pref[i];
    }
    debug(sc);
    vector<long long> suf(n + 1);
    for (int i = n; i > 0; --i) {
      suf[i - 1] = suf[i] + a[i - 1];
    }
    debug(suf);


    vector<long long> pref_mx(n + 1, -(long long) 1e15);
    for (int i = 0; i < n ; ++i) {
      pref_mx[i + 1] = max(pref_mx[i], b[i] - suf[i]);
    }
    debug(pref_mx);
    
    SparseTable mx(sc);
    long long sub = 0;
    auto get = [&](int cur, int x, long long need, bool bruh) {
      long long prof = pref[x + 1] - pref[cur + 1];
      long long price = max(0LL, mx.get(cur + 1, x) + sub);
      //cerr << "bs " << cur << ' ' << x << ' ' << price << ' ' << prof << ' ' << need << '\n';
      if (bruh) return 0LL + (need < price + prof);
      else return max(need - price - prof, 0LL) + price;
    };

    vector<int> res(n);
    for (int i = 0; i < n; ++i) {

      long long left = max(0LL, pref_mx[i + 1] + suf[i + 1]);
      res[i] = left;
      if (i == n - 1) {
        continue;
      }

      int ll;
      {

        int low = i + 1, high = n - 1;
        while (low < high) {
          int mid = (low + high) >> 1;
          if (get(i, mid, left, true)) {
            high = mid;
          } else {
            low = mid + 1;
          }
        }
        ll = low;
      }
      //cerr << i << ' ' << low << ' ' << left << '\n';
      res[i] = min(get(i, ll, left, false), 1LL * res[i]);

      if (ll > i + 1) {
        --ll;
        res[i] = min(get(i, ll, left, false), 1LL * res[i]);
      }

      {

        int low = i + 1, high = n - 1;
        while (low < high) {
          int mid = 1 + ((low + high) >> 1);
          if (get(i, mid, left, true)) {
            high = mid - 1;
          } else {
            low = mid;
          }
        }
        ll = low;
      }
      //cerr << i << ' ' << low << ' ' << left << '\n';
        res[i] = min(get(i, ll, left, false), 1LL * res[i]);

      if (ll > i + 1) {
        --ll;
        res[i] = min(get(i, ll, left, false), 1LL * res[i]);
      }

      sub += a[i];
    }

    return res;
  }; 

  auto first = solve();
  debug(first);

  
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  auto second = solve();
  debug(second);

  reverse(second.begin(), second.end());

  for (int i = 0; i < n; ++i) {
    cout << min(first[i], second[i]) << ' ';
    //cerr << first[i] << ' ' << second[i] << '\n';
  }
  cout << '\n';
  return 0;
  
}