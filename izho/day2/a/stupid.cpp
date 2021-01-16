#include<bits/stdc++.h>

using namespace std;

struct dsu {
  vector<int> par;
  dsu(int n) {
    par.resize(n);
    iota(par.begin(), par.end(), 0);
  } 

  int get(int v) {
    return (par[v] == v ? v : get(par[v]));
  }

  bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) {
      return false;
    }

    par[y] = x;
    return true;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  auto solve = [&](int n, vector<int> tt) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    long long ans = 0;
    int rr = 0;
    auto get = [&](vector<bool> a) {
      dsu d(n);
      int res = n;
      for (int i = 0; i < tt[0]; ++i) {
        int next = (i + 1) % tt[0];
        if ((a[next] ^ a[i]) == 1) {
          if (d.unite(next, i)) {
            --res;
          } else {
            --res;
            ++rr;
          }
        }
      }

      for (int i = 0; i < tt[1]; ++i) {
        int next = (i + 1) % tt[1];
        if ((a[next + tt[0]] ^ a[i + tt[0]]) == 1) {
          if (d.unite(next + tt[0], i + tt[0])) {
            --res;
          } else {
            --res;
          }
        }
      }

      return res;
    };

    vector<long long> all;
    do {
      long long res = 0;
      vector<bool> off(n, false);
      for (auto e : p) {
        off[e] = true;
        res += get(off);
      }
      all.push_back(res);
      ans += res;
    } while (next_permutation(p.begin(), p.end()));
    map<int, int> ct;
    for (auto e : all) {
      ++ct[e];
    }
    /*
    cerr << rr << '\n';
    for (auto[key, value] : ct) {
      cout << key << ' ' << value << '\n';
    }
    cout << '\n';
    cout << ans << '\n';
    */
    return make_pair(ans, rr);
  };
  int n;
  cin >> n;
  vector<int> foo(2);
  cin >> foo[0] >> foo[1];
  vector<long long> fac(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i;
  }
  
  auto[x, y] = solve(n, foo);
  cout << x << ' ' << y << '\n';
}