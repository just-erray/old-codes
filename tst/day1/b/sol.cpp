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
  for (int i = 0; i < int(v.size()); ++i) {
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(const T& v) {
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


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int x;
    cin >> x;
    --x;
    g[x].push_back(i + 1);
  }

  vector<int> ag(m);
  for (int i = 0; i < m; ++i) {
    cin >> ag[i];
    --ag[i];
  }
  
  const int LG = __lg(n) + 2;
  vector<vector<int>> lift(LG, vector<int>(n));
  vector<int> d(n);
  function<void(int)> Dfs_start = [&](int v) { 
    for (auto u : g[v]) {
      d[u] = d[v] + 1;
      lift[0][u] = v;
      Dfs_start(u);
    }
  };
  Dfs_start(0);
  for (int j = 1; j < LG; ++j) {
    for (int i = 0; i < n; ++i) {
      lift[j][i] = lift[j - 1][lift[j - 1][i]];
    }
  }

  debug(lift, d);
  auto Go_up = [&](int v, int x) {
    for (int i = 0; x > 0; ++i, x >>= 1) {
      if (x & 1) {
        v = lift[i][v];
      }
    }
    return v;
  };
  //0 caseini unutma 
  vector<int> ct(n);
  for (auto e : ag) {
    int depth = d[e];
    if (depth == 0) {
      ++ct[0];
      continue;
    }
    int till;
    if (depth % 2 == 0) {
      till = depth / 2 + 1;
    } else {
      till = (depth + 1) / 2;
    }
    int up = depth - till;
    int me = Go_up(e, up);
    ++ct[me];
  }  

  if (ct[0] > 0) {
    cout << 1 << '\n';
    return 0;
  }
  
  auto Can = [&](int x) {
    vector<int> size(n);
    function<void(int)> Dfs = [&](int v) {
      if (d[v] >= x) {
        size[v] = 1;
      }
      for (auto u : g[v]) {
        Dfs(u);
        size[v] += size[u];
      }
      size[v] -= ct[v];
    };
    Dfs(0);
    return (*min_element(size.begin(), size.end()) >= 0);
  };

  int low = 0, high = n;
  while (low < high) {
    int mid = ((low + high) >> 1) + 1;
    if (Can(mid)) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }
  cout << low + 1 << '\n';
}