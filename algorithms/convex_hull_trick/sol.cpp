// author: erray
#include<bits/stdc++.h>
 
using namespace std;

struct Line {
  
};

struct CHT {

};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }
  
  CHT cht;
  long long sum = 0;
  vector<long long> dp(n);
  for (int i = 0; i < n; ++i) {
    dp[i] = (sum + a[i]) * b[i] + cht.get(b[i]);
    cht.insert(-sum, dp[i]);
    sum += a[i];
  }
  
  for (auto e : dp) {
    cout << e << ' ';
  }

}