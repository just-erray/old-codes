// author: erray
#include<bits/stdc++.h>
 
using namespace std;

string s;

void solve(int ind) {
  if ((int) ind == s.size() - 1) {
    cout << s << '\n';
    return;
  }
  
  for (int j = ind; j < (int) s.size(); ++j) {
    swap(s[ind], s[j]);
    solve(ind + 1);
    swap(s[ind], s[j]);
  }
}

 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    s += char('0' + i);
  }
  
  solve(0);
}