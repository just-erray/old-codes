// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int k, x;
  cin >> k >> x;
  for (int i = x - k  + 1; i < x + k; ++i) {
    cout << i << ' ';
  }
}