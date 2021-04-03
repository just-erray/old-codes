// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int cur = 0;
  for (int i = 0; i < n; ++i) {
    cur ^= i;
    if (i % 2 == 0) {
      cout << bitset<5>(i).to_string() << ' ';
      cout << bitset<5>(cur).to_string() << '\n';
    }
  }
}