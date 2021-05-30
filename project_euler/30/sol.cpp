// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  vector<int> pw(256, 1);
  for (int i = '0'; i <= '9'; ++i) {
    int me = i - '0';
    for (int j = 0; j < 5; ++j) {
      pw[i] *= me;  
    }
  }
  int ans = 0;
  for (int i = 10; i < int(1e7); ++i) {
    int sum = 0;
    for (char c : to_string(i)) {
      sum += pw[c];
    } 
    ans += (sum == i) * i;
  }
  cout << ans << '\n';
}