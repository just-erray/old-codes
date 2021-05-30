// author: erray
#include <bits/stdc++.h>
 
using namespace std;
template<typename A, typename B> string to_string(const pair<A, B>& p);
template<typename A, typename B, typename C> string to_string(const tuple<A, B, C>& t);
template<typename A, typename B, typename C, typename D> string to_string(const tuple<A, B, C, D>& t);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char& c) {
  return string("'") + c + "'";
}

string to_string(const char *c) {
  return to_string(string(c));
}

string to_string(const bool& b) {
  return (b ? "true" : "false");
}

string to_string(const vector<bool>& v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if (i > 0) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<size_t T> string to_string(const bitset<T>& bs) {
  return bs.to_string();
}

template<typename T> string to_string(queue<T> q) {
  string res = "{";
  size_t sz = q.size();
  while (sz--) {
    T cur = q.front();
    q.pop();
    q.push(cur);
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(cur);
  }
  res += "}";
  return res;
}

template<typename T, class C> string to_string(priority_queue<T, vector<T>, C> pq) {
  vector<T> tmp;
  string res = "{";
  while (!pq.empty()) {
    T cur = pq.top();
    pq.pop();
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(cur);
    tmp.push_back(cur);
  }
  for (auto el : tmp) {
    pq.push(el);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(const T& v) {
  string res = "{";
  for (auto &el : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(el);
  }
  res += "}";
  return res;
}

template<typename A, typename B> string to_string(const pair<A, B>& p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename A, typename B, typename C> string to_string(const tuple<A, B, C>& t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ')';
}
template<typename A, typename B, typename C, typename D> string to_string(const tuple<A, B, C, D>& t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ", " + to_string(get<3>(t)) + ')';
}

void debug_out(int size, bool first, string name) {
  vector<string> tmp = {name};
  vector<int> tmp2 = {size, first};
  cerr << endl;
}

constexpr int buffer_size = 255;

template<typename Head, typename... Tail> void debug_out(int size, bool first, string name, Head H, Tail... T) {
  string tmp;
  int off = 0;
  while ((!name.empty() && name[0] != ',') || off != 0) {
    tmp += name[0];
    name.erase(name.begin());
    char c = tmp.back();
    if (c == '{' || c == '(') {
      ++off;
    } else if (c == '}' || c == ')'){
      --off;
    }
  }
  if (!name.empty()) {
    name.erase(name.begin());
  }
  if (tmp[0] == ' ') {
    tmp.erase(tmp.begin());
  }

  string buff = to_string(H);
  if ((int) buff.size() + size + (int) tmp.size() > buffer_size - 5 && !first) {
    cerr << '\n';
    size = 0;
  }
  cerr << '[' << tmp << ": " << buff << "] ";
  debug_out(((int) buff.size() + size + (int) tmp.size() + 5) % buffer_size, false, name, T...);
}

#ifdef DEBUG
#define debug(...) cerr << "-> ", debug_out(3, true, string(#__VA_ARGS__), __VA_ARGS__)
#define here cerr << "-> " << __LINE__ << endl
#else
#define debug(...) void(37)
#define here void(37)
#endif
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[y].push_back(x);
    g[x].push_back(y);
  }
  vector<int> con(n);
  for (int i = 0; i < n; ++i) {
    cin >> con[i];
  }

  vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2)));
  vector<vector<vector<int>>> ok(n, vector<vector<int>>(2, vector<int>(2)));
  // [node][from_up][turn on or of]
  function<void(int, int)> Dfs = [&](int v, int pr) {         
    vector<int> c;
    for (auto u : g[v]) {
      if (u != pr) {
        Dfs(u, v);
        c.push_back(u);
      }
    }
    for (int make = 0; make < 2; ++make) {
      for (int j = 0; j < 2; ++j) {
        int now = con[v] ^ make ^ j;
        int cur = make;
        vector<int> sw;
        bool out = false;
        for (auto u : c) {
          if (ok[u][make][0]) {
            cur += dp[u][make][0];
            if (ok[u][make][1]) {
              sw.push_back(u);
            }
          } else if (ok[u][make][1]) {
            cur += dp[u][make][1];
            now ^= 1;
          } else {
            out = true;
          }
        }
        if (out) {
          // ok[v][j][make] = false;
          break;
        }
        int& now_dp = dp[v][j][make];
        int& now_ok = ok[v][j][make];
        if (now == false) {
          now_dp = cur;
          now_ok = true;
        }
        sort(sw.begin(), sw.end(), [&](int x, int y) {
          return (dp[x][make][1] - dp[x][make][0]) < (dp[y][make][1] - dp[y][make][0]);
        });

        for (auto u : sw) {
          now ^= 1;
          cur += dp[u][make][1] - dp[u][make][0];
          if (now == false){
            now_dp = min(now_dp, cur);
            now_ok = true;
          }  
        }
      }      
    }
    debug(v, dp[v]);
  };
  Dfs(0, -1);
  int ans = INT_MAX;
  bool found = false;
  if (ok[0][0][0]) {
    ans = min(ans, dp[0][0][0]);
    found = true;
  }
  if (ok[0][0][1]) {
    ans = min(ans, dp[0][0][1]);
    found = true;
  }
  if (!found) {
    cout << "impossible" << '\n';
    return 0;
  }
  cout << ans << '\n';
}
