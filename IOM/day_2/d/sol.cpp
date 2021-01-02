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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, q;
  cin >> n >> m >> q;
  const uint64_t md = 1LL << 31;

  if (n <= 100 && m <= 100 && q <= 100) {
    vector<vector<uint64_t>> mat(n, vector<uint64_t>(m));
    while (q--) {
      int t, r1, c1, r2, c2;
      cin >> t >> r1 >> c1 >> r2 >> c2;
      --r1, --c1, --r2, --c2;
      if (t == 1) {
        int x;
        cin >> x;
        while (x--) {
          for (int i = r1; i <= r2; ++i) {
            for (int j = c1; j <= c2; ++j) {
              mat[i][j] = (mat[i][j] + 1) % md;
            }
          }
          ++c1;
          ++c2;
        }
      } else {
        uint64_t ans = 0;
        for (int i = r1; i <= r2; ++i) {
          for (int j = c1; j <= c2; ++j) {
            ans += mat[i][j];
            ans %= md;
          }
        }
        cout << ans << '\n';
      }
    }

    exit(0);
  }
  
  uint64_t ans = 0;
  while (q--) {
    int t, r1, c1, r2, c2;
    cin >> t >> r1 >> c1 >> r2 >> c2;
    if (t == 1) {
      int x;
      cin >> x;
      ans = (ans + uint64_t(r2 - r1 + 1) * (c2 - c1 + 1) % md * x  % md) % md;
    } else {
      cout << ans << '\n';
    }
  }
}