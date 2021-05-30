// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }

    int ans = 0;
    priority_queue<int> pq;
    long long sum = 0;
    for (auto e : a) {
      pq.push(-e);
      sum += e;
      while (sum < 0) {
        ++ans;
        sum += pq.top();
        pq.pop();
      }
    }
    cout << ans << '\n';
  }
}