// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  vector<int> ct(256);
  for (char c : s) {
    ++ct[c];
  }
  cout << ct['1'] << '\n';
}