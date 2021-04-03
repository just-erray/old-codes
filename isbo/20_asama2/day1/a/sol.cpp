//author: erray
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
  for (int i = 0; i < (int) v.size(); ++i) {
    if (i) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& e : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(e);
  }
  res += "}";
  return res;
}

template<typename A, typename B> string to_string(pair<A, B> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ")";
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) void(37)
#endif

struct Fenw {
  vector<int> tree;
  int n;
  Fenw(int _n) : n(_n) {
    tree.resize(n + 1);
  }

  void modify(int ind) {
    ++ind;
    while (ind <= n) {
      ++tree[ind];
      ind += ind & -ind;
    }
  }

  int get(int ind) {
    ++ind;
    int res = 0;
    while (ind) {
      res += tree[ind];
      ind -= ind & -ind;
    }
    return res;
  }

};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
  } 

  Fenw bit(n);
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    bit.modify(a[i]);
    debug(bit.get(a[i]));
    ans += (i + 1) - bit.get(a[i]);
  }
  cout << ans << '\n';
}