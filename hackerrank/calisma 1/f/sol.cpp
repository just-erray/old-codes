// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i];
    a[i] = m - a[i];
  }
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](auto x, auto y) {
    return a[x] > a[y];
  });
  
  int p = 0;
  priority_queue<int> pq;
  int ans = 0;

  for (int i = m - 1; i >= 0; --i) {
    while (p < n && a[ord[p]] == i) {
      pq.push(b[ord[p]]);;
      ++p;
    }
    if (pq.empty()) {
      continue;
    }
    ans += pq.top();
    pq.pop();
  }
  cout << ans << '\n';
}