//author: erray
#undef GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;

mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());

struct chash {
  int operator()(int x) const {
    static const int FIXED_RANDOM = rng();
    return x ^ FIXED_RANDOM;
  }
};

int xy;
const int N = 10000;

  int now = 0;
struct Trie {

  int way[N][2];
  bool trig[N];
  unordered_map<int, bool> st[N];

  long long ans = 0;

  Trie() {
    for (int i = 0; i < N; ++i) {
      way[i][0] = way[i][1] = -1;
      trig[i] = false;
    }
    
  }

  void push(int ind, int w) {
    int cur = 0;
    for (int l = 0; l < 12; ++l) {
      int go = ((ind >> l) & 1);
      if (!trig[cur]) {
        if (st[cur][w]) {
          ans += xy;
          trig[cur] = true;
        } else {
          st[cur][w] = true;
        }
      }

      if (way[cur][go] == -1) {
        way[cur][go] = ++now;
      }
      cur = way[cur][go];
    }
  }

};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, x, y;
  cin >> n >> x >> y;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
  }
  xy = x + y;
  const int mxN = (int) 1e3;
  long long ans[mxN][mxN];
  for (int i = 0; i < n; ++i) {
    Trie t;
    for (int j = i; j < n; ++j) {
      t.push(j, a[j]);
      ans[i][j] = 0LL + x + t.ans;
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l, --r;
    cout << ans[l][r] << '\n';
  }      
  cerr << now << '\n';
}