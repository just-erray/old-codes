#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  long long cur = 1LL * k * (k + 1) / 2;
  if (cur > n) {
    return cout << -1, 0;
  }

  cout << n - cur + k << '\n';

  for (int i = 1; i <= k; ++i) {
    cout << i << ' ';
  }

  for (int i = 0; i < n - cur; ++i) {
    cout << 1 << ' ';
  }
}