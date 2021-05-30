// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> st;
  for (int i = n - 1; i >= 0; --i) {
    while (!st.empty() && st.back() < a[i]) {
      st.pop_back();
    }
    st.push_back(a[i]);
  }
  cout << int(st.size()) << '\n';
}