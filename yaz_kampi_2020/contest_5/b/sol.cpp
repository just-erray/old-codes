// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<bool> sh(n);
  int t;
  cin >> t;
  while (t--) {
    int x;
    cin >> x;
    sh[x - 1] = true;
  }

  vector<int> st;
  for (int i = n - 1; i >= 0; --i) {
    if (!sh[i] && !st.empty() && st.back() == a[i]) {
      st.pop_back();
      continue;
    }
    st.push_back(a[i]);    
    a[i] = -a[i];
  }
  if (!st.empty()) {
    return cout << "NO\n", 0;
  }
  cout << "YES\n";
  for (auto el : a) {
    cout << el << ' ';
  }
}