// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int ans = 0;
  queue<int> que;
  multiset<int> ms;
  while (n--) {
    int t;
    cin >> t;
    if (t == 1) {
      int add;
      cin >> add;            
      que.push(add);
      ms.insert(add);
    } else {
      ans = max(ans, *prev(ms.end()) - *ms.begin());
      ms.erase(ms.find(que.front()));
      que.pop();  
    }
  }
  cout << ans << '\n';
}