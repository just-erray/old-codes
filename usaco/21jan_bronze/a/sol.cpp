// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string a, s;
  cin >> a >> s;
  assert((int) a.size() == 26);
  vector<int> pos(256);
  for (int i = 0; i < 26; ++i) {
    pos[a[i]] = i;   
  }

  int ans = 0;
  int cur = 37;
  for (char c : s) {
    if (pos[c] <= cur) {
      ++ans;
    } 
    
    cur = pos[c];
  }

  cout << ans << '\n';
}