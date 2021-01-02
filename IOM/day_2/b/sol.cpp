#include<bits/stdc++.h>

using namespace std;

template<typename A, typename B> string to_string(pair<A, B> p);
template<typename A, typename B, typename C> string to_string(tuple<A, B, C>);
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D>);

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(const char* p) {
  return to_string(string(p));
}

string to_string(char c) {
  return string("'") + c + "'";
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if ((int) res.size() > 1) {
      res += ", ";
    }             
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& el : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(el);
  }
  res += "}";
  return res;
}

template<typename A, typename B> string to_string(pair<A, B> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ')';
}
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ", " + to_string(get<3>(t)) + ')';
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << "  " << to_string(H);
  debug_out(T...);
}


#ifdef LOCAL
#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) void(37)
#endif

const int md = (int) 1e9 + 7;


int add(int x, int y) {
  return (x + y) % md;
}

int mul(int x, int y) {
  return 1LL * x * y % md;
}

int sub(int x, int y) {
  return 0LL + md + x - y % md;
}

int power(int x, int y) {
  int res = 1;
  while (y > 0) {
    if (y & 1) {
      res = 1LL * res * x % md;
    }
    y >>= 1;
    x = 1LL * x * x % md;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }  

  int ans = 0;
  function<int(int, int)> dfs = [&](int v, int pr) {
    int res = 1;
    int me = 0;
    for (auto u : g[v]) {
      if (u == pr) {
        continue;
      }
      int now = dfs(u, v);
      me = add(1, sub(me, power(2, now)));
      res += now;

    }
    
    me = sub(add(me, power(2, res)), 1); 
    debug(v, me);

    ans = add(ans, mul(me, (v + 1)));

    return res;
  };
  dfs(0, -1);

  cout << ans << '\n';
}