// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  cout << (n % 2 == 0 && n > 2 ? "YES" : "NO") << '\n';
}