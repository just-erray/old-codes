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
    auto tmp = a;
    sort(tmp.rbegin(), tmp.rend());
    if ((int) set<int>(a.begin(), a.end()).size() == n && a == tmp) {
      cout << "NO";
    } else {
      cout << "YES";
    }
    cout << '\n';
  }
}