#include<bits/stdc++.h>

using namespace std;


template<typename A, typename B> string to_string(pair<A, B>);
template<typename A, typename B, typename C> string to_string(tuple<A, B, C>);
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D>);

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(char c) {
  return "'"s + c + "'";
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
  for (const auto& el : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }  
    res += to_string(el);
  }
  res += "}";
  return res;
}


template<typename A, typename B> string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";  
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
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }   
  
  vector<int> sum(n, 1);
  for (int i = 0; i < n; ++i) {
    sort(g[i].begin(), g[i].end());  
  }
  vector<int> par(n);
  vector<vector<int>> sub(n);
  for (int i = 0; i < n; ++i) {
    sub[i].resize((int) g[i].size());
  }

  function<void(int)> dfs = [&](int v) {
    int cur = 0;
    for (auto u : g[v]) {
      if (u == par[v]) {
        continue;
      } 
      par[u] = v;
      dfs(u);
      sub[v][cur] = sum[u];
      sum[v] += sum[u];
      ++cur;
    }
  };
  dfs(0);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < (int) g[i].size(); ++j) {
      if (g[i][j] == par[i]) {
        sub[i][j] = n - sum[i];
      }
    }
  }
  debug(sub);

  function<int(int, int, int)> solve = [&](int v, int left, int from) {
    if (left == 0) {
      return v;
    }
    --left;

    int cur = 0;
    for (auto u : g[v]) {
      if (u == from) {
        continue;
      }
      if (sub[v][u] > left) {
        return solve(u, left, v);          
      } else {
        left -= sub[v][u];
      }
      ++cur;
    }
  };

  while (q--) {
    long long k;
    cin >> k;
    --k;
    int go = k / n;
    cout << k / n + 1 << ' ';
    cout << solve(k / n, k % n, -1) + 1 << '\n';
  }
}