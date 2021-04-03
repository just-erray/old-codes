// author: erray
#include<bits/stdc++.h>
 
using namespace std;

const int md = (int) 1e9 + 7;

int add(int x, int y) {
  return (x + y) % md;
}

int sub(int x, int y) {
  return ((x - y) + md) % md;
}

int mul(int x, int y) {
  return (1LL * x * y) % md;
}
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
  }  
  vector<int> w(n);
  for (int i = 0; i < n; ++i) {
    cin >> w[i];
  }
  vector<long long> cord(n);
  for (int i = 0; i < n - 1; ++i) {
    cord[i + 1] = cord[i] + w[i];
  }
  auto gauss = [&](int x) {
    return 1LL * x * (x + 1) / 2 % md;
  };
  vector<pair<int, long long>> st;
  int cur = 0;
  auto Get = [&](pair<int, long long> prev, pair<int, long long> next) {
    return next( 
  };

  auto Add = [&](int x, long long y) {
  };
  st.emplace_back(0, 0);
  for (int i = 0; i < n; ++i) {
    Add(h[i], cord[i]);
    ans = add(ans, );   
  }
}