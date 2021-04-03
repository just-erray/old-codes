// author: erray
#include<bits/stdc++.h>
 
using namespace std;

long long power(int x) {
  unsigned long long res = 1;
  unsigned long long b = 27;
  while (x > 0) {
    if (x & 1) {
      res *= b;
    }

    b *= b;
    x >>= 1;
  }

  return res;
}

struct Hash {
  unsigned long long hash = 0;
  int len = 0;

  void erase(char c) {
    assert(len > 0);
    --len;
    hash -= (c - 'a' + 1) * power(len);
  }

  void add(char c) {
    hash *= 27;
    hash += c - 'a' + 1;
    ++len;
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    Hash cur;
    for (int i = 0; i < k; ++i) {
      cur.add(s[i]);
    }

    set<unsigned long long> tot;
    tot.insert(cur.hash);
    for (int i = k; i < n; ++i) {
      cur.add(s[i]);
      cur.erase(s[i - k]);
      tot.insert(cur.hash);
    }

    cout << (int) tot.size() << '\n';
  }  
}