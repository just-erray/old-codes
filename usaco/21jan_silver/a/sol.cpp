// author: erray
#include<bits/stdc++.h>
 
using namespace std;

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> cur(n);
  iota(cur.begin(), cur.end(), 0);
  vector<set<int>>  tour(n);
  for (int i = 0; i < n; ++i) {
    tour[i].insert(i);
  }
  
  for (int i = 0; i < k; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;  
    swap(cur[x], cur[y]);
    tour[cur[x]].insert(x);
    tour[cur[y]].insert(y);
  }

  vector<int> go(n);
  for (int i = 0; i < n; ++i) {
    go[cur[i]] = i;
  }

  vector<set<int>> ans = tour;
  vector<int> bel(n);
  iota(bel.begin(), bel.end(), 0);
  for (int i = 0; i < n; ++i) {
    if (bel[i] != i) {
      continue;
    }

    int v = go[i];
    while (v != i) {
      ans[i].insert(tour[v].begin(), tour[v].end());
      bel[v] = i;      
      v = go[v];
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << (int) ans[bel[i]].size() << '\n';
  }
}