// author: erray
#include<bits/stdc++.h>

using namespace std;

long long md = 8999999999999999983;

const int M = (int) 2e5;
long long pw[M + 1];

long long chash(string s) {
  long long res = 0;
  for (int i = 0; i < (int) s.size(); ++i) {
    res = (res + __int128(s[i] - 'a' + 1) * pw[i]) % md;
  }  
  return res;
} 


int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  pw[0] = 27;
  for (int i = 0; i < M; ++i) {
    pw[i + 1] = ((__int128) pw[i] * 27) % md;
  }

  set<long long> occ;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    cout << chash(s) << '\n';
  } 
}