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

struct dsu {
  vector<int> par, sz;
  dsu(int n) {
    par.resize(n);
    sz.resize(n, 1);
    iota(par.begin(), par.end(), 0);
  }
  inline int get(int v) {
    return par[v] = (v == par[v] ? v : get(par[v]));
  }
  int size(int v) {
    return sz[get(v)];
  }
  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;
    sz[x] += sz[y];
    par[y] = x;
    return true;
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int h, w;
  cin >> h >> w;
  vector<string> a(h);
  for (int i = 0; i < h; ++i) {
    cin >> a[i];
  }
  dsu d(h + w);
  vector<vector<int>> g(h + w);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (a[i][j] == 'R') {
        g[i].push_back(h + j);
        g[h + j].push_back(i);
        d.unite(i, h + j);
      }
    }
  }
  debug(g);

  vector<tuple<char, int, int>> ans;
  auto Add = [&](int x, int y) {
    char c;
    if (y >= h) {
      c = 'Y';
      y -= h;
    } else {
      c = 'X';
      x -= h;
      swap(x, y);
    } 
    ans.emplace_back(c, x, y);
  };

  vector<bool> vis(h + w);
  function<void(int)> Dfs = [&](int v) {
    vis[v] = true;
    for (auto u : g[v]) {
      if (!vis[u]) {
        Dfs(u);
        Add(v, u);
      }  
    }
  };
  set<int> comp;
  for (int i = 0; i < h + w; ++i) {
    if (!g[i].empty()) {
      comp.insert(d.get(i));
    }
  }
  int size = int(comp.size());
  vector<int> ct(2);
  for (int i = 0; i < h + w; ++i) {
    ct[i >= h] += (!g[i].empty());
  } 
  debug(size);

  debug(ct);
  int vert = (ct[0] * w + (ct[1] - size) * (h - ct[0]));
  int hori = (ct[1] * h + (ct[0] - size) * (w - ct[1]));
  debug(vert, hori);
  if (vert < hori) {
    for (int i = 0; i < h; ++i) {
      if (!vis[i]) {
        Dfs(i);
      }
    }  
  } else {
    for (int i = h; i < h + w; ++i) {
      if (!vis[i]) {
        Dfs(i);
      }
    }  
  }

  cout << int(ans.size()) << '\n';
  for (auto e : ans) {
    cout << get<0>(e) << ' ' << get<1>(e) + 1 << ' ' << get<2>(e) + 1 << '\n';
  }
}