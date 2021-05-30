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
#define debug(...) void(37)
#define here void(37)
#endif
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n), rg(n);
  for (int i = 0; i < m; ++i) {
    int x, y, w;
    cin >> x >> y >> w;
    --x, --y;
    g[x].emplace_back(y, w);
    rg[y].emplace_back(x, w); 
  }

  vector<int> ord;
  vector<bool> vis(n);
  function<void(int)> Pre_dfs = [&](int v) {
    vis[v] = true;
    for (auto[u, w] : g[v]) {
      if (!vis[u]) {
        Pre_dfs(u);
      } 
    }
    ord.push_back(v);
  };
  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      Pre_dfs(i);
    }
  }
  vector<int> root(n);
  int cur_root = 0;
  function<void(int)> Scc_dfs = [&](int v) {
    vis[v] = true;
    root[v] = cur_root;
    for (auto[u, w] : rg[v]) {
      if (!vis[u]) {
        Scc_dfs(u);
      }
    }
  };
  
  reverse(ord.begin(), ord.end());
  debug(ord);
  vis.assign(n, false);
  vector<int> root_node;
  for (auto v : ord) {
    if (!vis[v]) {
      Scc_dfs(v);
      root_node.push_back(v);
      ++cur_root;
    }
  }

  debug(root);
  int size = cur_root;
  vector<int> Gcd(size);
  vector<long long> dist(n);
  vis.assign(n, false);
  for (int i = 0; i < size; ++i) {
    function<void(int)> Dfs = [&](int v) {
      vis[v] = true;
      vector<pair<int, int>> loops;
      for (auto[u, w] : g[v]) {
        if (root[u] != root[v]) {
          continue;
        }
        if (!vis[u]) {
          dist[u] = dist[v] + w;
          Dfs(u);
        } else {
          loops.emplace_back(u, w);
        }
      }
      for (auto[u, w] : loops) {
        debug(v, u, w, dist[v], dist[u]);
        Gcd[i] = gcd(Gcd[i], abs(dist[v] + w - dist[u]));
      }
    };
    Dfs(root_node[i]);
  }

  debug(Gcd);
  int q;
  cin >> q;
  while (q--) {
    int v, s, t;
    cin >> v >> s >> t;
    --v;
    int d = Gcd[root[v]];
    debug(d);
    //t * x + s = 0 mod d
    cout << (s % gcd(t, d) == 0 ? "YES" : "NO") << '\n';
  }

}