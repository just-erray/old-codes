// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n); 
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  const int N = (*max_element(a.begin(), a.end())) + 1;
  vector<int> ct(N);
  for (auto e : a) {
    ++ct[e];
  }

}