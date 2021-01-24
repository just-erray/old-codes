// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
  vector<vector<int>> sumr(2, vector<int>(n));
  vector<vector<int>> sumc(2, vector<int>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> a[i][j];
      sumr[i % 2][j] += a[i][j];
      sumc[j % 2][i] += a[i][j];
    }
  }

  long long ansr = 0;
  long long ansc = 0;

  for (int i = 0; i < n; ++i) {
    ansr += max(sumr[0][i], sumr[1][i]);
    ansc += max(sumc[0][i], sumc[1][i]);
  }
  
  cout << max(ansr, ansc) << '\n';
}