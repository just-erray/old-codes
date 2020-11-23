// author: erray
#include<bits/stdc++.h>
 
using namespace std;
template<typename A, typename B> string to_string(const pair<A, B>& p);
template<typename A, typename B, typename C> string to_string(const tuple<A, B, C>& t);
template<typename A, typename B, typename C, typename D> string to_string(const tuple<A, B, C, D>& t);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char& c) {
  return "'"s + c + "'";
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
#define debug(...) void(42)
#define here void(42)
#endif

int n;

vector<vector<int>> g;
vector<int> w;

vector<int> sz;
void dfs_sz(int v, int pr) {
  for (auto u : g[v]) {
    if (u == pr) {
      continue;
    }
    dfs_sz(u, v);
    sz[v] += sz[u];
  }    
}

vector<vector<int>> cg;
vector<map<int, pair<int, int>>> store;
vector<bool> vis;
vector<int> ord;

void dfs(int v, vector<array<int, 3>> par) {
  for (int i = 0; i < (int) par.size(); ++i) {
    par[i][1] ^= w[v];
    ++par[i][2];
  }

  int next = -1;
  for (auto u : g[v]) {
    if (sz[u] * 2 > sz[v]) {
      next = u;
    }
  }
  
  if (next == -1) {
    if (!par.empty()) {
      cg[par.back()[0]].push_back(v);
    }  
    for (auto[u, mask, size] : par) {
      store[u][v] = make_pair(mask, size);  
    }
    vis[v] = true;
    sz[v] = 0;
    ord.push_back(v);
    par.push_back({v, 0, 0});
    for (auto u : g[v]) {
      if (vis[u]) {
        continue;
      }
      dfs(u, par);
    }
  } else {
    int tmp = sz[v];
    sz[v] = sz[v] - sz[next];
    sz[next] = tmp;
    dfs(next, par);    
  }
} 
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  g.resize(n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  sz.resize(n, 1);
  dfs_sz(0, -1);
  debug(sz);

  w.resize(n);
  string foo;
  cin >> foo;
  for (int i = 0; i < n; ++i) {
    w[i] = (1 << (foo[i] - 'a'));
  }


  vis.resize(n);
  cg.resize(n);
  store.resize(n);
  dfs(0, {});
  reverse(ord.begin(), ord.end());
  
  debug(cg);
  debug(store);
  vector<vector<int>> mask(n);
  vector<long long> ans(n);
    

  for (int i = 0; i < n; ++i) {
    cout << ans[i] << " \n"[i == n - 1];
  }
}                 