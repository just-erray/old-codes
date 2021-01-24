// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;

  if (n == 2) {
    return cout << 4, 0;
  }

  if (n % 2 == 0) {
    return cout << 3, 0;
  }
  
  if (n % 3 == 1) {
    return cout << 3, 0;
  }

  return cout << 4, 0;


}
