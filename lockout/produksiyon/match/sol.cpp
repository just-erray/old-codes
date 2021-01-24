// author: erray
#include<bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  vector<string> a;
  while (!cin.eof()) {
    string s;
    getline(cin, s);
    a.push_back(s);
  }  

  shuffle(a.begin(), a.end(), rng);
  for (int i = 0; i < (int) a.size() - 1; i += 2) {
    cout << "Match " << (i + 2) / 2 << ": " << a[i] << " - " << a[i + 1] << '\n'; 
  }

  if ((int) a.size() % 2 == 1) {
    cout << a.back() << '\n';
  }
}