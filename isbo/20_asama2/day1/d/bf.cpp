//author: erray
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  function<void(int, int)> Solve = [&](int l, int r) {
    int ans = 0;
    for (int i = l; i < r; ++i) {
      
    }
    return ans;
  }; 
  cout << Solve(0, n - 1);
}