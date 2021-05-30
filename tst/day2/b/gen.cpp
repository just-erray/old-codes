#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> string to_string(pair<A, B> p);
string to_string(string s) {
  return '"' + s + '"';
}

string to_string(const char* c) {
  return to_string(string(c));
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < int(v.size()); ++i) {
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T& v) {
  string res = "{";
  for (auto& e : v) {
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(e);
  }
  res += "}";
  return res;
}
 
template<typename A, typename B> string to_string(pair<A, B> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << "  " << to_string(H);
  debug_out(T...);
}

#ifdef DEBUG 
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) void(37)
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int Rand(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  const int MAX = int(1e3);
  int n = Rand(1, 10);
  cout << n << '\n';
  vector<bool> vis(MAX);
  for (int i = 0; i < n; ++i) {
    int x = 1;
    do {
     x = Rand(1, MAX);
     debug(x);
    } while (vis[x]);
    vis[x] = true;
    cout << x << ' ' << Rand(0, 20) << '\n';
  }

}
