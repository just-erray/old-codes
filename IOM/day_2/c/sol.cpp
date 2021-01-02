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
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
  }
  vector<int> freq(m);
  for (int i = 0; i < n; ++i) {
    ++freq[a[i]];
  }
  int ans = 0;

  for (int i = 0; i < n; ++i) {
    vector<int> nf(m);
    for (int j = i - 1; j >= 0; --j) {
      ++nf[a[j]];
      if (abs(a[i] - a[j]) == 1) {
        vector<int> dp(m);
        dp[0] = 1;
        for(int q = 0; q < m; ++q) {
          if (q == a[i] || q == a[j]) {
            continue;
          }
          vector<int> new_dp(m);
          for (int k = 0; k < m; ++k) {
            if (k > 0) {
              new_dp[k] = mul(dp[k - 1], nf[q]);
            }
            new_dp[k] = add(new_dp[k], mul(dp[k], freq[q] - nf[q]));
          }
          swap(dp, new_dp);
        }                                                         

        for (int k = 0; k < m; ++k) {
          ans = add(ans, mul(dp[k], k + 1));  
        }    
        debug(i, j, dp); 
      }
    }  
  }
  cout << ans << '\n';
}