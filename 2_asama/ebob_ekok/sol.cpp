// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
const int md = (int) 1e9 + 7;
int add(int x, int y) {
  return (x + y) % md;
}

int sub(int x, int y) {
  return (x - y + md) % md;
}

int mul(int x, int y) {
  return 1LL * x * y % md;
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int x, y;
  long long n;
  cin >> x >> y >> n; 

}