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

struct Line {
  mutable long long a, b, p;
  bool query = false;
  bool operator< (const Line& ot) const { 
    if (query || ot.query) {
      return p < ot.p;
    } 
    return a < ot.a;
  }
};

const long long inf = (long long) 1e18;
struct LineContainer : multiset<Line> {
  long long divs(long long x, long long y) {
    return x / y - ((x ^ y) < 0 && x % y != 0);
  }

  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = inf;
      return false;
    }
    if (x->a == y->a) {
      x->p = (x->b > y->b ? inf : -inf);
    } else {
      x->p = divs(x->b - y->b, y->a - x->a);
    }
    return x->p >= y->p;
  }

  void add(int a, int b) {
    Line tmp;
    tmp.a = a;
    tmp.b = b;
    auto me = insert(tmp);
    auto nxt = next(me);
    while (isect(me, nxt)) {
      nxt = erase(nxt);
    }
    nxt = me;
    if (me != begin() && isect(--me, nxt)) {
      nxt = erase(nxt);
      isect(me, nxt);
    }
    while ((nxt = me) != begin() && isect(--me, nxt)) {
      isect(me, erase(nxt));
    }
  }

  long long get(long long x) {
    assert(!empty());
    Line tmp;
    tmp.p = x;
    tmp.query = true;
    auto me = lower_bound(tmp);
    return me->a * x + me->b;
  }
};

 
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  long long n;
  cin >> n;
  LineContainer lc;
  for (int i = 0; i < n; ++i) {
    long long x, y;
    cin >> x >> y;
    lc.add(x, y);
  }
  for (int i = 0; i < n; ++i) {
    long long x;
    cin >> x;
    cout << lc.get(x) << '\n';
  }
  
}