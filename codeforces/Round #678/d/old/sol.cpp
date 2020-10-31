// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T, typename F> string to_string(pair<T, F> p);
template<typename T, typename F, typename Tr> string to_string(tuple<T, F, Tr> p);
template<typename T, typename F, typename Tr, typename Th> string to_string(tuple<T, F, Tr, Th> p);
string to_string(string s) {
  return '"' + s + '"';
}
string to_string(char c) {
  return (string) "'" + c + "'";
}
string to_string(const char* p) {
  return to_string((string) p);
}
string to_string(bool B) {
  return (B ? "true" : "false");
}
string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if ((int) res.size() > 1) res += ", ";
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
template<size_t T> string to_string(bitset<T> bs) {
  return bs.to_string();
}
template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& el : v) {
    if ((int) res.size() > 1) res += ", ";
    res += to_string(el);
  }
  res += "}";
  return res;
}
template<typename T, typename F> string to_string(pair<T, F> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename T, typename F, typename Tr> string to_string(tuple<T, F, Tr> p) {
  return '(' + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ')';
}
template<typename T, typename F, typename Tr, typename Th> string to_string(tuple<T, F, Tr, Th> p) {
    return '(' + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ')';
}
void debug_out() {
  cerr << endl;
}
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" , debug_out(__VA_ARGS__)
#else
#define debug(...) (void) 37
#endif

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int x;
    cin >> x;
    g[x - 1].push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vector<int> ord;

  function<void(int)> dfs_b = [&](int v) {
    for (auto u : g[v]) {
      dfs_b(u);
    }  
    ord.push_back(v);
  };
  dfs_b(0);  

  auto check = [&](__int128 w) {
    vector<__int128> dp(n);
    for (auto v : ord) {
      __int128 take = 0;
      for (auto u : g[v]) {
        take += dp[u];
      }
      if (g[v].empty()) {
        take = w;
      }
      dp[v] = take - a[v];
      if (dp[v] < 0) {
        return false;
      }
    }
    return true; 
  };

  __int128 low = 0, high = (__int128) 2e14;
  while (low < high) {
    __int128 mid = (low + high) >> 1;
    if (!check(mid)) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  string res;
  while (low) {
    res += char('0' + low % 10);
    low /= 10;
  }
  reverse(res.begin(), res.end());
  cout << res << '\n';
}