// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  set<char> st(s.begin(), s.end());
  cout << ((int) st.size() == 1 ? "Won" : "Lost") << '\n';
}