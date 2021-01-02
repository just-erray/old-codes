// author: erray
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = 123092838;
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int k, n;
  cin >> k >> n;
  vector<pair<long long, long long>> a(k);
  for (int i = 0; i < k; ++i) {
    cin >> a[i].first >> a[i].second;
    assert(a[i].second > 0);
  }

  unordered_map<long long, int, custom_hash> ct;
  int ans = 0;
  //map<long long, int> ct;
  for (int i = 0; i < k; ++i) {
    long long v = a[i].first;
    long long cur = 0;
    for (int j = 0; j < n; ++j) {
      cur += v;          
      ans = max(ans, ++ct[cur]);
      ++v;
      if (j % a[i].second == a[i].second - 1) {
        v = a[i].first;  
      }
    }
  }

  cout << ans << '\n';
}