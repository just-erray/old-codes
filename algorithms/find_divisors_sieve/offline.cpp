// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  const int N = (int) 1e6 + 1;
  vector<int> lst(N, -1);
  int q;
  cin >> q;
  vector<array<int, 3>> qs(q);
  for (int i = 0; i < q; ++i) {
    cin >> qs[i][0] >> qs[i][1];
    qs[i][2] = i;
  }

  sort(qs.begin(), qs.end(), [&](auto x, auto y) {
    return x[1] < y[1];
  });

  int p = 2;
  vector<int> ans(q);
  for (auto[n, l, id] : qs) {
    while (p <= l) {
      for (int j = p; j < N; j += p) {
        lst[j] = p;
      }
      ++p;
    }
    if (lst[n] == -1) {
      continue;
    }
    int add = lst[n];
    //solution and stuff  
  }
}