// author: erray
#include<bits/stdc++.h>

using namespace std; 
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  try
  {
  ifstream in("int");
  int n;
  in >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  bool ok = true;
  for (int i = 1; i < n; ++i) {
    ok &= (a[i] >= a[i - 1]);    
  }
  multiset<int> tmp(a.begin(), a.end());
  for (int i = 0; i < n; ++i) {
    int x;
    in >> x;
    if (!tmp.count(x)) {
      throw "Array is different";      
    } else {
      tmp.erase(tmp.find(x));
    }
  }
  if (!ok) {
    throw "Array is not sorted";
  }
  throw "OK";
  }
  catch (const char* c) {
    cout << c << '\n';
  }
}

