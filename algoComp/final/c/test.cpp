// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cout << "for " << i  << ": ";
    for (int j = i + 1; j <= n; ++j) {
      int bet = i ^ j;
      if (bet < j && bet > i) {
        cout << j << ' ';
      }
    }

    cout << endl;
  }
}