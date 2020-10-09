// author: erray
#include<bits/stdc++.h>
 
using namespace std;

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
 namespace divs {

  vector<int> check_primes;
  void createSieve(long long limit) {
    check_primes = sieve::list((int) ceil(sqrt(limit)));
  }

  vector<pair<long long, int>> prime(long long n, bool fast = false) {
    assert(n > 0);
    vector<pair<long long, int>> res;
    if (!fast) {
      for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) res.emplace_back(i, 0);
        while (n % i == 0) {
          n /= i;
          ++res.back().second;
        }
      }
    } else {
      assert(!check_primes.empty());
      for (int i = 0; i < (int) check_primes.size() && 1LL * check_primes[i] * check_primes[i] <= n; ++i) {
        if (n % check_primes[i] == 0) res.emplace_back(check_primes[i], 0);
        while (n % check_primes[i] == 0) {
          n /= check_primes[i];
          ++res.back().second;
        }
      }
    }
    if (n > 1) res.emplace_back(n, 1);
    return res;
  }

  vector<vector<int>> till(int n) {
    vector<vector<int>> res(n + 1);
    for (int i = 2; i <= n; ++i) {
      if (!res[i].empty()) continue;
      for (int j = i; j <= n; j += i) {
        res[j].push_back(i);
      }
    }
    return res;
  }

  vector<long long> all(long long n) {
    assert(n > 0);
    vector<long long> res;
    for (long long i = 1; i * i <= n; ++i) {
      if (n % i == 0) {
        res.push_back(i);
        res.push_back(n / i);
      }
    }
    assert(res.size() >= 2);
    if (res.back() == res[(int) res.size() - 2]) res.pop_back();
    return res;
  }

  bool isPrime(long long n, bool fast = false) {
    if (!fast) {
      for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
      }
    } else {
      assert(!check_primes.empty());
      for (int i = 0; i < (int) check_primes.size() && 1LL * check_primes[i] * check_primes[i] <= n; ++i) {
        if (n % check_primes[i]) return false;
      }
    }
    return true;
  }
} 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<set<int>> ins(n);
  long long ans = 0;
  for (int i = 1; i < n; ++i) {
    auto d = divs::all(i);
    int sum = accumulate(d.begin(), d.end(), 0) - i;
    if (sum >= n) {
      continue;
    }
    if (sum < i) {
      if (ins[i].count(sum)) {
        ans += sum + i;
      }  
    } else {
      ins[sum].insert(i);
    }
  }
  cout << ans << '\n';
}