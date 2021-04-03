// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = (int) 1; i <= n; ++i) {
    ofstream out("int");
    out << 1 << ' ' << i << '\n';
    out.close();
    system("sol.exe <int >out");
    cout << i << endl;
    system("checker.exe <out");
  }
}