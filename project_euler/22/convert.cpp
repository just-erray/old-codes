// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  for (char c : s) {
    if (c != '"') {
      if (c == ',') {
        cout << ' ';
      } else {
        cout << c;
      }
    }
  }
}