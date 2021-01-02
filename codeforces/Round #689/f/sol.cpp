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

  string s;
  cin >> s;
  vector<bool> have(256);
  for (char c : s) {
    have[c] = true;
  }


  if ((int) s.size() == 1) {
    for (int i = 0; i < n; ++i) {
      cout << a[i];
      if (i < n - 1) {
        cout << s[0];
      }
    } 
    
    return 0;
  }

  if (!have['x']) {
    for (int i = 0; i < n; ++i) {
      cout << a[i];
      if (i < n - 1) {
        cout << '+';
      }
    } 
    
    return 0;    
  }

  if (have['-']) {
  
  } else {
    
  }
}