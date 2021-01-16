#include<bits/stdc++.h>

using namespace std;

#define int int64_t

const int md = (int) 1e9 + 7;

int add(int x, int y) {
  return (x + y) % md;
}

int sub(int x, int y) {
  return (x - y + md) % md;
}

int mul(int x, int y) {
  return (1LL * x * y) % md;
}

int power(int x, int y) {
  int res = 1;
  while (y > 0) {
    if (y & 1) {
      res = (1LL * res * x) % md;
    }

    y >>= 1;
    x = (1LL * x * x) % md;
  }

  return res;
}


int divis(int x, int y) {
  return mul(x, power(y, md - 2));
}

vector<int> fac(2, 1);

int fact(int x) {
  while ((int) fac.size() <= x) {
    fac.push_back(mul(fac.back(), (int) fac.size()));
  }
  return fac[x];
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
    --p[i];
  }
  
  vector<int> g;
  vector<bool> vis(n);
  for (int i = 0; i < n; ++i) {
    if (vis[i]) {
      continue;
    }

    int v = i;
    int size = 0;
    while (!vis[v]) {
      vis[v] = true;
      ++size;
      v = p[v];
    }
    g.push_back(size);
  }
 
  vector<int> trash(n + 1); 
  trash[2] = 2;
  for (int i = 4; i <= n; i += 2) {
    trash[i] = mul(trash[i - 2], mul(i / 2, i / 2));
  }

  int ans = mul(n, mul(n, fact(n)));
  vector<int> f(n + 1);
  f[2] = 1;
  for (int i = 3; i <= n; ++i) {
    f[i] = mul(f[i - 1], i + 1);
  }
  f[n] = mul(f[n], 2);

  for (auto e : g) {
    if (e == 1) {
      continue;
    }
    if (e == 2) {
      ans = sub(ans, f[n]);  
      continue;
    }
    ans = add(ans, mul(trash[e], divis(fact(n + 1), fact(e + 1))));
    ans = sub(ans, mul(f[n], e));
  }
  cout << ans << '\n';
}