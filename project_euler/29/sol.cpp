// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int a, b;
  cin >> a >> b;
  using Big = vector<pair<int, int>>;
  set<Big> st;
  for (int i = 2; i <= a; ++i) {
    Big me;
    int tmp = i;
    for (int j = 2; j <= tmp; ++j) {
      if (tmp % j != 0) {
        continue;
      }
      me.emplace_back(j, 0);
      while (tmp % j == 0) {
        ++me.back().second;
        tmp /= j;
      }
    }
    Big add = me;
    for (int j = 0; j < b - 1; ++j) {
      for (int k = 0; k < int(add.size()); ++k) {
        add[k].second += me[k].second;
      }
      st.insert(add);
    }
  }
  cout << int(st.size()) << '\n';
}