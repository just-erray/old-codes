// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long n, a, b;
  cin >> n >> a >> b;
  if (b < a) {
    swap(a, b);
  }
  long long dist = b - a;
  if (dist % 2 == 0) {
    cout << dist / 2 << '\n';
  } else {
    long long go = min(n - b, a - 1);
    cout << go + (dist + 1) / 2 << '\n';
  }

}