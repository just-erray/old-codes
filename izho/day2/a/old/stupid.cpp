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
  auto solve = [&](int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    long long ans = 0;
    int rr = 0;
    auto get = [&](vector<bool> a) {
      dsu d(n);
      int res = n;
      for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        if ((a[next] ^ a[i]) == 1) {
          if (d.unite(next, i)) {
            --res;
          } else {
            --res;
            ++rr;
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
  vector<long long> fac(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i;
  }
  
  vector<long long> d(n + 1);
  for (int i = 2; i <= n; ++i) {
    auto[x, y] = solve(i);
    cout << x << ' ' << y << '\n';
    d[i] = x;
    int lost = fac[i] * i * i - d[i]; 
    cerr <<  lost << ' ' << lost / (i * 2) << '\n';
  }
}