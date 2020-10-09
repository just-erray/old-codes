// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T> class graph {
  int n;
  vector<vector<int>> g;

};



 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  graph g(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    g.add(x, y);
  }
  
}
