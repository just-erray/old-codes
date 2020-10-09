// author: erray
#include<bits/stdc++.h>
 
using namespace std;
using namespace chrono;

#define rn high_resolution_clock::now()
 
int main (int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int ct = 0;
  for (char c : string(argv[1])) {
    ct *= 10;
    ct += c - '0';  
  }
  for (int j = 0; j < ct; ++j) {
    system("./gen.exe >int");
    auto s = rn; 
    system("./sol.exe <int >checker_out");
    cout << duration_cast<microseconds>(rn - s).count() << " ms" << endl;
    system("./checker.exe <checker_out");    
  }
}
