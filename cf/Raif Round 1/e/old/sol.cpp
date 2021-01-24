// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  
  vector<vector<int>> grid(n);
  int lst = -1;
  vector<pair<int, int>> ans;

  auto imp = [&] {
    cout << -1 << '\n';
    exit(0);
  };

  if (a.back() == 2 || a.back() == 3) { 
    imp();
  }

  int take = n - 1;
  for (int i = 0; i < n; ++i) {
    if (a[i] == 0) {
      continue;
    }  
    if ((int) ans.size() > 1 && ans.back().second == take && ans[(int) ans.size() - 2].second == take) {
      ++take;
    }
    if (a[i] == 1) {      
      if (lst == 3) {
        ans.emplace_back(i, take);
        ans.emplace_back(i, take - 1);
        --take;
      } else {
        ans.emplace_back(i, take);        
      }
      lst = -1;
      --take;   
    } else if (a[i] == 2) {
      if (lst == 3) {
        ans.emplace_back(i, take);
        ans.emplace_back(i, take - 1);
        --take;
      } else {
        ans.emplace_back(i, take);        
      }
      lst = 2;
    }  else {
      if (lst == 3) {
        ans.emplace_back(i, take);
        ans.emplace_back(i, take - 1);
        --take;
      } else {
        ans.emplace_back(i, take);        
      }
      lst = 3;     
    }
  }

  if (lst != -1) {
    imp();
  }
  
  for (auto[l, r] : ans) {
    if (r >= n) {
      imp();
    }
  }

  cout << (int) ans.size() << '\n';
  for (auto[l, r] : ans) {
    cout << l + 1 << ' ' << r + 1 << '\n';
  }
}