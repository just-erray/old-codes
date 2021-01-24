// author: erray
#include<bits/stdc++.h>
 
using namespace std;

const int inf = (int) 1e9;

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "redistricting";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, k;
  string foo;
  cin >> n >> k >> foo;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = (foo[i] == 'H' ? 1 : -1);
  }
  //debug(a);

  multiset<pair<int, int>> st;
  st.emplace(0, 0);
  vector<int> dp(n + 1);
  vector<int> pref(1, 0);

  for (int i = 0; i < n; ++i) {
    pref.push_back(pref.back() + a[i]);
    auto p = *st.begin();
    dp[i + 1] = p.first + (p.second >= pref.back());
    //debug(i, st);
    if (i >= k - 1) {
      st.erase(st.find(make_pair(dp[i - k + 1], pref[i - k + 1])));
    }
    st.emplace(dp[i + 1], pref[i + 1]);
  }

  //debug(dp);
  cout << dp.back() << '\n';
}
