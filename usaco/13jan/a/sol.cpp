// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "curling";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n;
  cin >> n;
  vector<pair<int, int>> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }

  for (int i = 0; i < n; ++i) {
    cin >> b[i].first >> b[i].second;
  }

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  auto 
  auto ConvexHull = [&](vector<pair<int, int>> x, bool upper = false) {
    vector<pair<int, int>> res;
    
    auto del = [&] {
      if ((int) res.size() < 2) {
        return false;
      }

      vector<pair<int, int>> m(res.end() - 3, res.end());
      return upper ^ (1LL * (m[2].second - m[0].second) * (m[1].first - m[0].first) < 1LL * (m[1].second - m[0].second) * (m[2].first - m[0].first)); 
    };
    
    for (auto e : x) {
      res.push_back(e);
      while (del()) {
        res.erase(res.end() - 2);
      }
    }

    return res;
  };

  auto angle = [&](pair x, pair y) {
    return (y.second - x.second) * 1.0 / (y.second - x.second);
  };
  
  auto la = ConvexHull(
}