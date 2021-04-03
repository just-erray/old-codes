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

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> can(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> can[i][j];
    }
  } 

  vector<vector<int>> dp(n + 1, vector<int>(m));
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < m; ++j) {
      dp[i][j] = (can[i][j] ? 0 : dp[i + 1][j] + 1);
    }
  }


  vector<vector<int>> ans(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](auto x, auto y) {
      return dp[i][x] < dp[i][y];
    });
    vector<int> size(m);
    {
      set<int> cur;
      cur.insert(-1);
      cur.insert(m);
      for (auto e : ord) {
        auto me = cur.insert(e).first;
        size[e] = *next(me) - *prev(me) - 1;
      }
    }

    multiset<int> active;
    vector<vector<int>> by_order(n + 3);
    for (auto e : ord) {
      by_order[dp[i][e]].push_back(size[e]);
      active.emplace(size[e]);
    }

    int fixed = 0;
    for (int j = i; j < n; ++j) {
      int cur = j - i + 1;
      for (auto e : by_order[cur - 1]) {
        active.erase(active.find(e));
        fixed = max(fixed, (cur - 1) * e);
      }

      debug(active, fixed);
      if (active.empty()) {
        ans[i][j] = fixed;
        continue;
      }
      ans[i][j] = max(fixed, (*prev(active.end())) * cur);
    }
  }

  for (int i = n - 2; i >= 0; --i) {
    for (int j = 0; j < n; ++j) {
      ans[i][j] = max(ans[i][j], ans[i + 1][j]);
    }
  }
  debug(ans);
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l, --r;
    cout << ans[l][r] << '\n';
  }
}