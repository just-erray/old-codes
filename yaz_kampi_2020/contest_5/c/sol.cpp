// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> ct(2);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    ++ct[x % 2];
  }
  int take = n - k;

  auto even = [&] {
    cout << "Daenerys\n";
    exit(0);
  };

  auto odd = [&] {
    cout << "Stannis\n";
    exit(0);
  };

  if (take == 0) {
    (ct[1] % 2 ? odd() : even());
  }

  if (ct[1] <= take / 2) {
    even();
  }

  if (take % 2 == 0) {
    if (k % 2 == 0) {
      even();
    } else {
      if (ct[0] <= take / 2) {
        odd();
      }
      even();
    }
  } else {
    if (k % 2 == 0) {
      if (ct[0] <= take / 2) {
        even();
      }
      odd();
    } else {
      odd();
    }
  }

}