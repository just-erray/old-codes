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

struct dsu {
  vector<int> par, sz;
  dsu(int n) {
    par.resize(n);
    sz.resize(n, 1);
    iota(par.begin(), par.end(), 0);
  }

  inline int get(int x) {
    return par[x] = (par[x] == x ? x : get(par[x]));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (par[x] == par[y]) {
      return false;
    }
    sz[x] += sz[y];
    par[y] = x;
    return true;
  }

  int size(int x) {
    return sz[get(x)];
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<set<int>> g(n);
  vector<set<int>> ids(n);
  vector<bool> vis(n);
  long long ans = 0;
  dsu d(n);
  dsu ud(n);
  vector<array<int, 2>> es(m);
  set<array<int, 2>> av;

  function<void(int, int)> Merge = [&](int x, int y) {
    if (!vis[y]) {
      --ans;
    }  
    if (!vis[x]) {
      --ans;
    }
    vis[x] = vis[y] = true;
    x = d.get(x);
    y = d.get(y);
    if (x == y) {
      return;
    }
    if (int(g[x].size()) < int(g[y].size())) {
        swap(x, y);
    }
    
    debug(g[x], g[y]);
    int unique = int(g[x].size());
    for (auto e : g[y]) {
      if (g[x].count(e)) {
        --unique;
        continue;
      }
      g[x].insert(e);
      ans += d.size(x);
    }
    ans += 1LL * unique * d.size(y); 

    vector<pair<int, int>> nw;
    int px = ud.get(x);
    int py = ud.get(y);
    if (int(ids[px].size()) < int(ids[py].size())) {
      swap(px, py);
    }
    for (auto e : ids[py]) {
      if (ids[px].count(e)) {
        ids[px].erase(e);
        continue;
      }  
      if (av.count(es[e])) {
        av.erase(es[e]);
        if (es[e][0] == py) {
          es[e][0] = px;
        } else {
          es[e][1] = px;
        }
        if (av.count({es[e][1], es[e][0]})) {
          nw.emplace_back(es[e][0], es[e][1]);
        } else {
          ids[px].insert(e);
          av.insert(es[e]);
        }
      }
    }

    ud.unite(px, py);
    d.unite(x, y);
    for (auto[v, u] : nw) {
      Merge(v, u);
    }
  };

  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    int py = d.get(y);
    int px = d.get(x);
    int ux = ud.get(x);
    int uy = ud.get(y);
    es[i] = {ux, uy};
    bool unite = av.find({uy, ux}) != av.end();
    if (px != py) {
      if (!g[py].count(x)) {
        ans += d.size(py);
        g[py].insert(x);     
        ids[ux].insert(i);
        ids[uy].insert(i);
        av.insert({ux, uy});
      }
      debug(ans);

      if (unite) {
        av.erase({uy, ux});
        Merge(x, y);
      } 
    }

    cout << ans << '\n';
  }
}