// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;

  n *= 2;
  cout << n * n / 4 - (n % 4 != 0) << '\n';
}