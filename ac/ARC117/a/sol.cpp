// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int a, b;
  cin >> a >> b;
  bool rev = false;
  if (a < b) {
    rev = true;
    swap(a, b);
  }
  
  vector<long long> ans;
  long long sum =  0;
  for (int i = 0; i < a; ++i) {
    sum += i + 1;
    ans.push_back(i + 1);
  }

  sum -= 1LL * b * (b + 1) / 2;
  int left = sum % b;
  for (int i = b - 1; i >= 0; --i) {
    ans.push_back(-(i + 1 + sum / b + (left > 0)));
    --left;
  }
  for (auto e : ans) {
    cout << e  * (rev ? -1 : 1) << ' ';
  }

}