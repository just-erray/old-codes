// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  const int N = (int) 1e6 + 1;
  vector<vector<int>> divs(N);
  for (int i = 1; i < N; ++i) {
    for (int j = i; j < N; j += i) {
      divs[j].push_back(i);
    }
  } 
}