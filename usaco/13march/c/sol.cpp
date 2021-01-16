// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "fcount";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 0; i < n + 1; ++i) {
    cin >> a[i];
  }

  auto can = [&n](vector<int> ct) {
    for (int i = n; i > 0; i -= (ct[i] == 0)) {
      if (ct[i] == 0) {
        continue;
      }
      --ct[i];
      int me = i;
      int p = i;
      vector<int> next;

      while (me--) {
        while (p > 0 && ct[p] == 0) {
          --p;
        }  

        if (p == 0) {
          return false;
        }

        next.push_back(p);
        --ct[p];
      }
      
      for (auto e : next) {
        ++ct[e - 1];
      }

    }

    return true;
  };
  
  vector<int> ans;
  vector<int> ct(n + 1);
  for (auto e : a) {
    ++ct[e];
  }

  for (int i = 0; i < n + 1; ++i) {
    --ct[a[i]];
    if (can(ct)) {
      ans.push_back(i);
    } 
    ++ct[a[i]];
  }

  cout << (int) ans.size() << '\n';
  for (auto e : ans) {
    cout << e + 1 << '\n';
  }
}