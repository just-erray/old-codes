// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string s;
  int q;
  cin >> n >> s >> q;
  string left, right;
  for (int i = 0; i < n * 2; ++i ){
    (i < n ? left : right) += s[i];
  }
  bool reversed = false;
  while (q--) {
    int t, a, b;
    cin >> t >> a >> b;
    --a, --b;
    if (t == 2) {
      reversed ^= true;
      continue;
    }

    bool aright, bright;
    {
      bool r = false;
      if ((a < n && reversed) || (a >= n && !reversed)) {
        r = true;
      }
      if (a >= n) {
        a -= n;
      }  
      aright = r;
    }

    {
      bool r = false;
      if ((b < n && reversed) || (b >= n && !reversed)) {
        r = true;
      }
      if (b >= n) {
        b -= n;
      }
      bright = r; 
    }

    swap((aright ? right[a] : left[a]), (bright ? right[b] : left[b]));
  }

  if (reversed) {
    swap(left, right);
  }
  cout << left << right << '\n';
}