// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string s;
  cin >> n >> s;
  vector<int> a(n + 1);
  for (int i = 0; i <= n; ++i) {
    cin >> a[i];
  }

  vector<int> add(n + 1);
  for (int i = 0; i < n; ++i) {
    add[i + 1] = add[i] + (s[i] == '<' ? 1 : -1);
  }

  int mn = *min_element(add.begin(), add.end());
  for (int i = 0; i <= n; ++i) {
    add[i] -= mn;                                                
  }

  vector<vector<int>> ans;
  while (true) {
    vector<int> new_a(n + 1);
    for (int i = 0; i <= n; ++i) {
      new_a[i] = a[i] - add[i];
    }
    bool ok = *min_element(new_a.begin(), new_a.end()) >= 0;
    for (int i = 0; i < n; ++i) {
      ok &= (((new_a[i] < new_a[i + 1]) == (s[i] == '<')) && new_a[i] != new_a[i + 1]);
    }
    if (!ok) {
      ans.push_back(a);
      break;
    }
    ans.push_back(add);
    swap(new_a, a);
  }
  cout << (int) ans.size() << '\n';
  for (auto e : ans) {
    for (auto ee : e) {
      cout << ee << ' ';
    }
    cout << '\n';
  }

}