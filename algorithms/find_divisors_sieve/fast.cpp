// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  const int N = (int) 1e6 + 1;
  vector<int> cnt(N);
  for (int i = 2; i < N; ++i) {
    for (int j = i; j < N; j += i) {
      ++cnt[j];
    } 
  }

  vector<int> pref(N + 1);
  for (int i = 0; i < N; ++i) {
    pref[i + 1] = pref[i] + cnt[i];
  }

  vector<int> all(pref[N]);
  auto b = pref;
  for (int i = 2; i < N; ++i) {
    for (int j = i; j < N; j += i) {
      all[b[j]++] = i;
    }
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int n, l;
    cin >> n >> l;
    if (l < all[pref[n]]) {
      continue;
    }
    int add = *prev(lower_bound(all.begin() + pref[n], all.begin() + pref[n + 1], l + 1));
    //solution and stuff
  }
}