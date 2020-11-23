// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int a, b, l, r;
  cin >> a >> b >> l >> r;
  --l, --r;
  int sum = (a + b);
  int now = l * (l / sum);
  l -= now;
  r -= now;
  int size = min(r + 1, sum * 2);
  int ans = INT_MAX; 
  auto get = [&](string s) {
    erase(s.begin(), s.begin() + l);
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    return (int) s.size();
  };

  if (a < b) {
    int no = b - a;
    string now(min(size, b), 'a');
    size -= min(size, b);
    string add(min(a, size));
    size -= (int) add.size();
    iota(add.begin(), add.end(), 'b');
    now += add;
    int can = min(size, b);
    {
      string tmp = now;
      tmp += string(can, 'a');
      can = size - can;
      string nadd(can);
      iota(nadd.begin(), nadd.end(), 'b');
      tmp += nadd;
      ans = max(ans, get(tmp));
    }
    {
    
    }  
  } else {
  
  }
  cout << ans << '\n';
}
