// author: erray
#include<bits/stdc++.h>
 
using namespace std;

class dsu {
  public:
  vector<int> par, ct;
  dsu(int n) {
    par.resize(n);
    ct.resize(n, 1);
    iota(par.begin(), par.end(), 0);
  }
  inline int get(int v) {
    return par[v] = (v == par[v] ? v : get(par[v]));
  }
  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;
    ct[x] += ct[y];
    par[y] = x;
    return true;
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  int sm = m;
  dsu d(n);
  vector<int> deg(n);
  vector<bool> act(n);
  int self = 0;
  long long ans = 0;
  int check = 0;
  while (m--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    act[x] = act[y] = true;
    check = x;
    if (x == y) {
      ++self;
      continue;
    }
    d.unite(x, y);
    ans += deg[x]++;
    ans += deg[y]++;
  }
  if (d.ct[d.get(check)] != accumulate(act.begin(), act.end(), 0)) {
    return cout << 0, 0;
  } 
  cout << ans + 1LL * (self - 1) * self / 2 + 1LL * self * (sm - self) << '\n';

}