// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, t;
  cin >> n >> t;
  int k;
  cin >> k;
  auto Ask = [&](int l, int r) {
    cout << "? " << l + 1 << ' ' << r + 1 << endl;
    int res;
    cin >> res;
    return res;
  };

  int low = 0, high = n - 1;
  while (low < high) {
    int mid = (low + high) >> 1;
    if (Ask(0, mid) > mid + 1 - k) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  cout << "! " << low + 1 << endl;
}