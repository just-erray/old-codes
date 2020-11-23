// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;

  auto ask = [&](int x, int y, int mood) {
    if (mood == 1) {
      cout << "AND";
    } else if (mood == 2) {
      cout << "OR";
    } else {
      cout << "XOR";
    }
    
    cout << ' ' << x + 1 << ' ' << y + 1 << endl;
    int res;
    cin >> res;
    return res;
  };

  vector<int> x(n);
  vector<int> vis(n);
  vis[0] = 0;
    
  int f = -1;
  for (int i = 1; i < n; ++i) {
    x[i] = ask(0, i, 0);
    if (vis[x[i]] || x[i] == 0) {
      f = i;
    } else {
      vis[x[i]] = i;
    }
  }

  int res = 0;
  if (f != -1) {
    res = ask(f, vis[x[f]], 2);
    res ^= x[f];
  } else {
    int ind = -1;
    for (int i = 1; i < n; ++i) {
      if (x[i] == n - 1) {
        ind = i;
      }
    }
    assert(ind != -1);
    int fd = 1 + (ind == 1);
    res = ask(fd, ind, 1) + ask(0, fd, 1);  
    res ^= x[fd];
  }
  
  cout << "! ";
  for (auto el : x) {
    cout << (res ^ el) << ' ';
  }
  cout << endl;
}