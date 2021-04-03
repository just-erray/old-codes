// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "sisugungobegi";
  freopen((P + ".gir").c_str(), "r", stdin);
  freopen((P + ".cik").c_str(), "w", stdout);
  #endif 
  long long s, n, g;
  cin >> s >> n >> g;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }
  sort(a.begin(), a.end());
  for (auto[x, c] : a) {
    if (g + x >= s) {
      break;
    }
    g = min(s - x, g + c);
  }
  cout << g << '\n';
}