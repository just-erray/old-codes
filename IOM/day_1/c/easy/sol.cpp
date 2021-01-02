#include<bits/stdc++.h>

using namespace std;

const int N = (int) 2e5 + 5;
vector<int> g[N];

int get(int v, int& left, int pr) {
  if (left == 0) {
    return v + 1;
  } 
  --left;
  int res = -1;
  for (auto u : g[v]) {
    if (u == pr) {
      continue;
    }
    if (res != -1) {
      break;
    } 
    res = get(u, left, v);
  }
  return res; 
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  for (int i = 0; i < n; ++i) {
    sort(g[i].begin(), g[i].end());
  }
  while (q--) {
    long long k;
    cin >> k;
    --k;
    int s = k / n;
    cout << s + 1 << ' ';
    int left = k % n;
    cout << get(s, left, -1) << '\n';
  }
}