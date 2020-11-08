// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int sx, sy, tx, ty;
  cin >> sx >> sy >> tx >> ty;
  string ans;
  auto add_x = [&](int x, int nx) {
    ans += string(abs(nx - x), (x > nx ? 'L' : 'R'));
  };

  auto add_y = [&](int y, int ny) {
    ans += string(abs(y - ny), (y > ny ? 'D' : 'U'));
  };
  
  auto add = [&](int x, int y, int nx, int ny, bool top = true) {
    if (top) {
      add_x(x, nx);
      add_y(y, ny);
    } else {
      add_y(y, ny);    
      add_x(x, nx);
    } 
  };

  ans += 'U';
  add(sx, sy + 1, tx - 1, ty, false);
  ans += 'R';

  ans += 'D';
  add(tx, ty - 1, sx + 1, sy, false);
  ans += 'L';
  
  ans += 'L';
  add(sx - 1, sy, tx, ty + 1, false);
  ans += 'D';

  ans += 'R';
  add(tx + 1, ty, sx, sy - 1, false);
  ans += 'U';

  cout << ans << '\n';
}