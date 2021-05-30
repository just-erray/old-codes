// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string s;
  cin >> n >> s;
  queue<int> que;
  for (int i = 0; i < n - 2; ++i) {
    if (s.substr(i, 3) == "fox") {
      que.push(i); 
    }
  }

  set<int> active;
  for (int i = 0; i < n; ++i) {
    active.insert(i);
  }

  auto Check = [&](auto check) {
    if (check == prev(active.end()) || check == prev(prev(active.end()))) {
      return;
    }
 
    if (s[*check] == 'f' && s[*next(check)] == 'o' && s[*next(next(check))] == 'x') {
      que.push(*check);
    }
    
  };

  int ans = 0;
  while (!que.empty()) {
    ++ans;
    int ind = que.front();
    que.pop();
    for (int j = 0; j < 3; ++j) {
      active.erase(active.lower_bound(ind));
    }
    auto check = active.lower_bound(ind);
    for (int j = 0; j < 2; ++j) {
      if (check == active.begin()) {
        continue;
      }
      check = prev(check);
      Check(check);
    }
  }
  cout << n - ans * 3 << '\n';
}