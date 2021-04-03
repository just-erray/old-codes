// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
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

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
      return a[x] < a[y];
    });

    vector<int> ans;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += a[ord[i]];
      if (i == n - 1 || sum >= a[ord[i + 1]]) {
        ans.push_back(ord[i]);
      }
    }


    sort(ans.begin(), ans.end());

    cout << (int) ans.size() << '\n';
    for (auto e : ans) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}