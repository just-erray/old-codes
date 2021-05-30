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

struct SegTree {
  int n;
  vector<int> mn;
  SegTree(int _n) : n(_n) {
    mn.resize(n << 1, int(1e9 + 1));
  } 
  
  int get(int l, int r) {
    int res = INT_MAX;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res = min(res, mn[l++]);
      }
      if (r & 1) {
        res = min(res, mn[--r]);
      }
    }
    return res;
  }

  void modify(int p, int x) {
    for (mn[p += n] = x; p > 1; p >>= 1) {
      mn[p >> 1] = min(mn[p], mn[p ^ 1]);
    }
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, root;
  cin >> n >> root;
  --root;
  vector<int> s(n);
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  vector<int> start(n), end(n);
  vector<int> tour;
  vector<int> d(n);
  function<void(int, int)> Dfs = [&](int v, int pr) {
    start[v] = int(tour.size());
    tour.push_back(v);
    for (auto u : g[v]) {
      if (u == pr) {
        continue;
      }
      d[u] = d[v] + 1;
      Dfs(u, v);
    }
    end[v] = int(tour.size());
    tour.push_back(v);
  };
  Dfs(root, -1);

  debug(start, end, tour);
  debug(d);
  int q;
  cin >> q;
  vector<array<int, 3>> qs(q);
  for (int i = 0; i < q; ++i) {
    cin >> qs[i][0] >> qs[i][1];
    --qs[i][0];
    qs[i][2] = i;
  } 
  sort(qs.begin(), qs.end(), [&](auto x, auto y) {
    return d[x[0]] + x[1] < d[y[0]] + y[1];
  });

  SegTree st(n * 2);
  vector<vector<int>> add_ord(n);
  for (int i = 0; i < n; ++i) {
    add_ord[d[i]].push_back(i);
  }
  int p = 0;
  vector<int> ans(q);
  for (auto[v, dist, id] : qs) {
    debug(v, dist);
    int till = min(n - 1, d[v] + dist);
    debug(till);
    while (p <= till) {
      for (auto e : add_ord[p]) {
        st.modify(start[e], s[e]);
      }
      ++p;  
    }
    ans[id] = st.get(start[v], end[v]);
  }
  for (auto e : ans) {
    cout << e << '\n';
  }
}