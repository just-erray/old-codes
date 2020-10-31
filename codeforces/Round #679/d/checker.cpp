// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  ofstream cc("checker_result");
  ifstream in("int");
  //cin is code's output, in is input of the code
  try {
    int n;
    in >> n;
    vector<int> add(n);
    string ans;
    cin >> ans;
    if (ans == "NO") {
      throw "OK";
    }
    for (int i = 0; i < n; ++i) {
      cin >> add[n - 1 - i];
    }
    set<int> s;
    for (int i = 0; i < n * 2; ++i) {
      char c;
      cin >> c;
      if (c == '+') {
        s.insert(add.back());
        add.pop_back();  
      } else {
        int x;
        in >> x;
        if (*s.begin() != x) {
          throw "WA";
        }
        s.erase(s.begin());
      }
    }

    throw "OK";      
    
  } catch(const char* c) {
    if (c == "OK") {
      cc << 1;
      cout << "\033[" << 32 << "m" << c << '\n';
    } else {
      cc << 0;
      cout << "\033[" << 31 << "m" << c << '\n';
    }   
  }
  cout << "\033[" << 37 << "m";
}