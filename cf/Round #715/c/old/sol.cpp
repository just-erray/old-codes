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
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  vector<array<int, 3>> edges(m);
  int extra = 0;
  for (int i = 0; i < m; ++i) {
    int x, y, w;
    cin >> x >> y >> w;
    --x, --y;
    g[x].emplace_back(y, w);
    g[y].emplace_back(x, w); 
    edges[i] = {x, y, w};
    extra ^= w;
  }

  bool loop = false;
  dsu d(n);
  vector<pair<int, int>> zero;
  for (int i = 0; i < n && !loop; ++i) {
    sort(g[i].begin(), g[i].end());
    int p = 0;
    for (int j = 0; j < n; ++j) {
      if (p < g[i].size() && g[i][p].first == j) {
        ++p;
        continue;
      }
      if (i == j) {
        continue;
      }
      if (i < j) {
      debug(i, j);
        zero.emplace_back(i, j);
        if (!d.unite(i, j)) {
          loop = true;
          break;
        }
      }
                           
    }
  }

  if (loop) {
    //extra = trash
    here; 
    long long ans = 0;
    dsu bel(n);
    vector<set<int>> no(n);
    for (int i = 0; i < n; ++i) {
      for (auto[u, foo] : g[i]) {
        no[i].insert(u);
      }
    }

    set<int> in;
    for (int i = 0; i < n; ++i) {
      in.insert(i);
    }

    for (int i = 0; i < n; ++i) {
      debug(in);
      if (!in.count(i)) {
        continue;
      }
      in.erase(i);
      
      auto tmp = no[i];
      for (auto e : tmp) {
        if (in.count(e)) {
          in.erase(e);
        }
      }

      vector<int> fine_addition_to_my_collection;
      function<void(int, int)> Unite = [&](int v, int u) {
        if (bel.unite(v, u)) {
          fine_addition_to_my_collection.push_back(u);
          if (int(no[v].size()) < int(no[u].size())) {
            swap(no[v], no[u]);
          }
          vector<int> add;
          for (auto e : no[v]) {
            if (no[u].count(e) == 0) {
              add.push_back(e);
            }
          }
          debug(v, u, add);
          debug(no[v], no[u]);
          for (auto e : add) {
            no[v].erase(e);
          }
          for (auto e : add) {
            Unite(v, e);
          }
        } 
      };

      for (auto e : in) {
        Unite(i, e);
      }

      for (auto e : fine_addition_to_my_collection) {
        if (in.count(e)) in.erase(e);
      }
      for (auto e : tmp) {
        if (bel.get(e) != bel.get(i)) {
          in.insert(e);
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      debug(bel.get(i));  
    }
    for (auto[v, u, w] : edges) {
      if (bel.unite(v, u)) {
        ans += w;
      }
    }
    cout << ans << '\n';
  } else {
    //use extra 
    //n = sqrt(m)
    //brute force trash one 
    sort(edges.begin(), edges.end(), [&](auto x, auto y) {
      return x[2] < y[2];
    });

    vector<array<int, 3>> new_edges;
    dsu usef(n);
    for (auto[v, u, w] : edges) {
      if (usef.unite(v, u)) {
        new_edges.push_back({v, u, w});
      }
    }
    swap(new_edges, edges);
    
    long long ans = 0;
    {
      long long res = extra;
      for (auto[v, u, w] : edges) {
        if (d.unite(v, u)) {
          res += w;
        }
      }
      ans = res;
    }

    {
      long long my_ans = LLONG_MAX;
      for (int i = 0; i < (int) zero.size(); ++i) {
        dsu rd(n);
        for (int j = 0; j < (int) zero.size(); ++j) {
          if (i != j) {
            rd.unite(zero[j].first, zero[j].second);
          }
        }
        long long res = 0;
        for (auto[v, u, w] : edges) {
          if (rd.unite(v, u)) {
            res += w;
          }
        }   
        my_ans = min(my_ans, res);
      } 
      ans = min(ans, my_ans);
    }
    cout << ans << '\n';
  }
}