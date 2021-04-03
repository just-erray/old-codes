// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int cur = 0;
  int c = 0;
  for (int i = n - 1; i; --i) {
    cur ^= i;
    cout << bitset<5>(cur).to_string() << '\n';
  }
}