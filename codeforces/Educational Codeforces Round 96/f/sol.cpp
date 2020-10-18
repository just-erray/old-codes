// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> l(n), r(n);
  vector <long long> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> l[i] >> r[i] >> a[i];
  }
  vector<int> tl, tr;
  vector <long long> ta;
  int ll = 0, rr = -1;
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    if (rr < l[i]) {
      if (i > 0) {
        tl.push_back(ll);
        tr.push_back(rr);
        ta.push_back(sum);
      }
      sum = 0;
      ll = l[i];
      rr = r[i];
    } else {
      rr = r[i]; 
    }
    sum += a[i];
  }
  tl.push_back(ll);
  tr.push_back(rr);
  ta.push_back(sum);
  swap(tl, l); 
  swap(tr, r); 
  swap(ta, a); 
  

   
}