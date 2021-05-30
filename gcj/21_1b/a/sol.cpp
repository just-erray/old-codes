// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  const int mul[] = {1, 12, 720};
  const long long MAX = 360 * 12 * (long long) 1e10;
  const long long HOUR = MAX / 12;
  const long long MINUTE = MAX / 60;
  const long long SECOND = MAX / 60 / 60;
  int T;
  cin >> T;
  for (int tt = 1; tt <= T; ++t) {
    cout << "Case #" << tt << ": ";
    array<long long, 3> a;
    cin >> a[0] >> a[1] >> a[2];
    sort(a.begin(), a.end());
    [&] {
      do {
        long long h, m, s, ms;
        s = a[2] / SECOND;   
        m = a[1] / MINUTE;
        h = a[0] / HOUR;
        vector<long long> old_a = a;
        a[0] -= h * HOUR + 



        swap(old_a, a);
      } while (next_permutation(a.begin(), a.end()));
    }();
    cout << '\n';
  }
}