#undef LOCAL
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
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
  }

  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int x, int y) {
    return c[x] > c[y];
  });


  vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[ord[i]] = i;
  }
  
  vector<set<pair<int, int>>> g(n);
  for (int i = 0; i < n; ++i) {
    g[i].emplace(pos[i], pos[i]);
  }
  
  auto f = [&](int v) {
    if ((*g[v].begin()).first != 0) {
      return 0;
    }
    return (*g[v].begin()).second + 1;
  };

  auto get = [&](int v) {
    int u = f(v);
    if (u > n - 1) {
      return 0;
    }
    
    v = pos[v];
    if (u < v) {
      swap(u, v);
    }
    return c[ord[v]] + c[ord[u]] + c[ord[(v == 0) + (u == 1)]];
  };

  
  auto add = [&](int t, int v, int u) {
    u = pos[u];
    if (t == 1) {
      auto nw = g[v].lower_bound({u, u});
      int l = u, r = u;
      if (nw != g[v].begin() && (*prev(nw)).second == u - 1) {
        l = (*prev(nw)).first;
        g[v].erase(prev(nw));  
      }
      
      nw = g[v].lower_bound({u, u});
      if (nw != g[v].end() && (*nw).first == r + 1) {
        r = (*nw).second;
        g[v].erase(nw);
      }
      g[v].emplace(l, r);
    } else {
      auto nw = prev(g[v].lower_bound({u + 1, -1}));
      if ((*nw).first != u) {
        g[v].emplace((*nw).first, u - 1);
      }
      nw = prev(g[v].lower_bound({u + 1, -1}));
      if ((*nw).second != u) {
        g[v].emplace(u + 1, (*nw).second);
      }
      g[v].erase(prev(g[v].lower_bound({u + 1, -1})));
    }
  };

  multiset<int> ans;
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    add(1, x, y);
    add(1, y, x);
  }
  
  for (int i = 0; i < n; ++i) {
    ans.insert(get(i));    
  }
  debug(g);

  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    --x, --y;
    ans.erase(ans.find(get(x)));
    ans.erase(ans.find(get(y)));
    add(t, x, y);
    add(t, y, x);
    ans.insert(get(x));
    ans.insert(get(y));
    cout << *prev(ans.end()) << '\n';
    debug(g);
  }
}