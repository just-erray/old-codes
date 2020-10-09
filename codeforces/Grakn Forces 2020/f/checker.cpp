// author: erray
#include<bits/stdc++.h>
 
using namespace std;
#define __int128 __int128_t
namespace sieve {
  vector<int> list(int n) {
    assert(n <= (int) 3e8 && n >= 0);
    if (n == 0) return vector<int>(0);
    vector<int> res;
    vector<bool> ip(n + 1, true);
    for (int i = 2; i <= n; ++i) {
      if (!ip[i]) continue;
      res.push_back(i);
      if ((int) ceil(1.0 * n / i) < i) continue;
      for (int j = i * i; j <= n; j += i) {
        ip[j] = false;
      }
    }
    return res;
  }

  vector<bool> check(int n) {
    assert(n <= (int) 3e8 && n >= 0);
    if (n == 0) return vector<bool>(1, false);
    vector<bool> ip(n + 1, true);
    for (int i = 2; i <= n; ++i) {
      if (!ip[i]) continue;
      if (ceil(1.0 * n / i) < i) continue;
      for (int j = i * i; j <= n; j += i) {
        ip[j] = false;
      }
    }
    ip[0] = false;
    if (n > 1) ip[1] = false;
    return ip;
  }
}

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ofstream cc("checker_result");
  ifstream in("int");
  //cin is code's output, in is input of the code
  try {
    int n;
    in >> n;
    vector<pair<int, int>> ans;
    int sz;
    cin >> sz;
    ans.resize(sz);
    for (int i = 0; i < sz; ++i) {
      cin >> ans[i].first >> ans[i].second;
    }
    vector<__int128> a(n);
    auto primes = sieve::list((int) 1e6);
    for (int i = 0; i < n; ++i) {
      a[i] = primes[i];    
    }
    shuffle(a.begin(), a.end(), rng);
    auto f = [&](int x, int y) {
      __int128 tmp = a[x] * a[y];
      a[x] = tmp;
      a[y] = tmp;      
    };
    for (auto[x, y] : ans) {
      f(x - 1, y - 1);
    }
    sort(a.begin(), a.end());
    int ct = 1;
    for (int i = 1; i < n; ++i) {
      ct += (a[i] != a[i - 1]);
    } 
    if (ct > 2) {
      throw "WA";
    } else {
      throw "OK";
    }
  } catch(const char* c) {
    if (c == "OK") {
      cc << 1;
      cout << "\033[" << 32 << "m" << c << '\n';
    } else {
      cc << 0;
      cout << "\033[" << 31 << "m" << c << '\n';
    }   
  }
  cout << "\033[" << 37 << "m";
}