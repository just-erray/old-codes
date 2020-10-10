// author: erray
#include<bits/stdc++.h>
 
using namespace std;

string sum(string x, string y) {
  if ((int) x.size() < (int) y.size()) {
    swap(x, y);
  }
  string res;
  bool left = false;
  for (int i = 0; i < (int) x.size(); ++i) {
    int v = x[i] - '0';
    int v2 = 0;
    if (i < (int) y.size()) {
      v2 = y[i] - '0';
    }
    int nw = v2 + v + left;
    res += char('0' + (nw % 10));
    left = (nw >= 10);
  }
  if (left) {
    res += '1';
  }
  return res;
}
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int ans = 0;
  vector<string> fib(2, "1");
  while ((int) fib.back().size() < n) {
    fib.push_back(sum(fib[0], fib[1]));
    fib.erase(fib.begin());
    ++ans;
    if (ans < 10) {
      cerr << fib.back() << '\n';    
    }
  }
  cout << ans + 2 << '\n';
}