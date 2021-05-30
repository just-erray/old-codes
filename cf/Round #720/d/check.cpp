// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  vector<int> deg(100);
  while (!cin.eof()) {
    int x, y;
    cin >> x >> y;
    ++deg[x];
    ++deg[y];
    assert(deg[x] <= 2 && deg[y] <= 2);
  }
}