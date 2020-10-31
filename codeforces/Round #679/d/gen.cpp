// author: erray
#include<bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n = 10;
  cout << n;
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  shuffle(a.begin(), a.end(), rng);
  int left = 0;
  for (int i = 0; i < n; ++i) {
    cout << a[i] << '\n'; 
    ++left;
    int get = rng() % (left + 1);
    left -= get;
    while (--get) {
      cout << "-\n";
    }
  }
  while (left--) {
    cout << "-\n";  
  }
}