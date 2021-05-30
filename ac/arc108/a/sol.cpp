// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long s, p;
  cin >> s >> p;
  long long low = 1, high = s / 2;
  while (low < high) {
    long long mid = (low + high) >> 1;
    if (p / mid + !!(p % mid) <= (s - mid)) {
      high = mid; 
    } else {
      low = mid + 1;
    }
  }

  cout << (low * (s - low) == p ? "Yes" : "No") << '\n';
}