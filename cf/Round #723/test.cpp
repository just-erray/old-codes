// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  try {
   cout << "hi\n";
   throw "sa";
  } catch (const char* res) {
    cout << res << endl;
    assert(false);
  }
}


