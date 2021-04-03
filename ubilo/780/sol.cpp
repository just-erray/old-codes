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
  return (string) "'" + c + "'";
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

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

class dsu {
  public:
  vector<int> par, size;
  vector<array<int, 3>> rb;
  dsu(int n) {
    par.resize(n);
    size.resize(n, 1);
    iota(par.begin(), par.end(), 0);
  }
  inline int get(int v) {
    if (par[v] == v) {
      return v;
    } 
    rb.push_back({v, par[v], 0});
    return par[v] = get(par[v]);
  }
  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;

    rb.push_back({x, x, size[y]});
    rb.push_back({y, y, 0});
    size[x] += size[y];
    par[y] = x;
    return true;
  }
  void roll_back() {
    reverse(rb.begin(), rb.end());
    for (auto[v, par_v, dec] : rb) {
      par[v] = par_v;
      size[v] -= dec;
    }
    rb.clear(); 
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "gezi";
  freopen((P + ".gir").c_str(), "r", stdin);
  freopen((P + ".cik").c_str(), "w", stdout);
  #endif 
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    cin >> edges[i].first >> edges[i].second;
    --edges[i].first, --edges[i].second;
  }

  int q;
  cin >> q;   
  vector<array<int, 3>> queries(q);
  for (int i = 0; i < q; ++i) {
    for (int j = 0; j < 3; ++j) {
      cin >> queries[i][j];
      queries[i][j] -= (j < 2);
    }
  } 

  debug(queries, edges);



  dsu cur(n);
  vector<int> ans(q);
  function<void(int, int, vector<int>)> Solve = [&](int l, int r, vector<int> qs) {
    if (l == r) {
      for (auto e : qs) {
        ans[e] = l + 1;
      } 
      return;
    }
    
    int mid = (l + r) >> 1;
    cur.rb.clear();
    auto Add = [&] {
      for (int i = l; i <= mid; ++i) {
        cur.unite(edges[i].first, edges[i].second);
      }
    };

    Add();

    vector<int> left, right;
    for (auto i : qs) {
      auto[v, u, z] = queries[i];
      v = cur.get(v);
      u = cur.get(u);
      int res = cur.size[v] + (v != u) * cur.size[u];
      if (res >= z) {
        left.push_back(i);
      } else {
        right.push_back(i);
      }
    }

    cur.roll_back();
    Solve(l, mid, left);
    Add();
    Solve(mid + 1, r, right);
  };

  vector<int> qs(q);
  iota(qs.begin(), qs.end(), 0);
  Solve(0, m - 1, qs);

  for (auto e : ans) {
    cout << e << '\n';
  }

    
  
}