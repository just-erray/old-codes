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
	cout << accumulate(a.begin(), a.end(), 0LL) << '\n';	
	
}
