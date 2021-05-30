// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ifstream ch("out");
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    set<pair<int, int>> es;
    for (int i = 1; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      es.emplace(x, y);
    }
    int size;
    ch >> size;
    for (int i = 0; i < size; ++i) {
      int x1, x2, y1, y2;
      ch >> x1 >> y1 >> x2 >> y2;
      if (es.count({x1, y1}) == 0) {
        swap(x1, y1);
      }
      es.emplace(x2, y2);
      es.erase({x1, y1});
    }

    for (auto[v, u] : es) {
      cout << v << ' ' << u << '\n';
    }
  }
}