// author: erray
#include <bits/stdc++.h>
 
using namespace std;
 template<typename A, typename B> string to_string(pair<A, B> p);
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t);
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t);

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(char c) {
  return string("'") + c + "'";
}

string to_string(const char* c) {
  return to_string(string(c));
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

template<size_t T> string to_string(bitset<T> bs) {
  return bs.to_string();
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < int(v.size()); ++i) {
    if (i > 0) {
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
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + '}';
}
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ", " + to_string(get<3>(t)) + '}';   
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

long long gcd(long long x, long long y) {
  return (y ? gcd(y, x % y) : x);
}
 
struct fract {
  long long t;
  long long b;
  void normalize() {
    long long d = gcd(t, b);
    t /= d;
    b /= d;
  }
  fract(long long _t = 0, long long _b = 1) : t(_t), b(_b) { normalize(); }
  bool operator<(const fract& ot) {
    long long d = gcd(b, ot.b);
    long long dt = gcd(t, ot.t);
    return __int128(1) * (t / dt) * (ot.b / d) < __int128(1) * (ot.t / dt) * (b / d);
  }
  bool operator==(const fract& ot) {
    return t * ot.b == ot.t * b;
  }
  void operator+=(const fract& ot) {
    long long d = gcd(b, ot.b);
    t = ot.b / d * t + b / d * ot.t;
    b = b / d * ot.b;
    normalize();
  }
};

fract operator/(const fract& me, const fract& ot) {    
  long long d = gcd(me.b, ot.b);
  long long dt = gcd(me.t, ot.t);
  return fract((me.t / dt) * (ot.b / d), (me.b / d) * (ot.t / dt));
}

string to_string(fract x) {
  return to_string(x.t) + "/" + to_string(x.b);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, l;
  cin >> n >> l;
  vector<vector<int>> v(n, vector<int>(l));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < l; ++j) {
      cin >> v[i][j];
    }
  }

  vector<vector<fract>> dv(n, vector<fract>(n - 1));
  for (int i = 0; i < n; ++i) {
    int sum = 0;
    int ind = 0;
    int tot = accumulate(v[i].begin(), v[i].end(), 0);
    fract one = fract(tot, n);
    fract now = one;
    debug(i);
    debug(tot);
    debug(one);
    for (int j = 0; j < n - 1; ++j) {
      while (fract(sum + v[i][ind]) < now) {
        assert(ind < l);
        debug(sum);
        debug(v[i][ind]);
        debug(now);
        sum += v[i][ind];
        ++ind;
      }
      fract left = now;
      left += fract(-sum);
      dv[i][j] = left / fract(v[i][ind]);
      dv[i][j] += fract(ind);
      now += one;
    }
    assert(now == fract(accumulate(v[i].begin(), v[i].end(), 0)));
  }

  debug(dv);


  vector<int> p(n);
  vector<fract> ans(n - 1);
  vector<bool> vis(n);
  for (int j = 0; j < n - 1; ++j) {
    int use = -1;
    for (int i = 0; i < n; ++i) {
      if (!vis[i] && (use == -1 || dv[i][j] < dv[use][j])) {
        use = i;
      }
    }
    vis[use] = true;
    p[j] = use;
    ans[j] = dv[use][j];
  }
  int left = 0;
  while (vis[left]) {
    ++left;
  }
  p[n - 1] = left;

  for (int i = 0; i < n - 1; ++i) {
    cout << ans[i].t << ' ' << ans[i].b << '\n';
  }
  for (int i = 0; i < n; ++i) {
    cout << p[i] + 1 << ' ';
  }
}                                                                        