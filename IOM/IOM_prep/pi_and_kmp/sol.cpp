// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s, t;
  cin >> s >> t;
  int n = (int) s.size();
  vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    pi[i] = pi[i - 1];
    while (pi[i] > 0 && pi[i] != s[i]) {
      pi[i] = pi[pi[i] - 1];
    }
    pi[i] += (s[i] == s[p[i]]);
  }
}