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
#define debug(...) void(37)
#define here void(37)
#endif

template<typename T, typename F = function<T(const T&, const T&)>> class SparseTable {
  public:
  int sz, lg;
  vector<vector<T>> table;
  F cal;
  SparseTable() { }
  SparseTable(vector<T> v, F _cal) : cal(_cal) {
    sz = (int) v.size();
    lg = 32 - __builtin_clz(sz);
    table.resize(lg);
    table[0] = v;
    for (int i = 1; i < lg; ++i) {
      table[i].resize(sz - (1 << i) + 1);
      assert(sz - (1 << i) + 1 >= 0);
      for (int j = 0; j < (int) table[i].size(); ++j) {
        table[i][j] = cal(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  T get(int l, int r) {
    assert(l >= 0 && r < sz && l <= r);
    int clg = 31 - __builtin_clz(r - l + 1);
    return cal(table[clg][l], table[clg][r - (1 << clg) + 1]);
  }
};

struct Fenw {
  vector<int> a;
  int n;
  Fenw(int _n) : n(_n) {
    a.resize(n + 1);
  }

  int get(int ind) {
    ++ind;
    int res = 0;
    while (ind > 0) {
      res += a[ind];
      ind -= ind & -ind;
    }
    return res;
  }

  void modify(int ind, int add = 1) {
    ++ind;
    while (ind <= n) {
      a[ind] += add;
      ind += ind & -ind;
    }
  }
};

 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
    --c[i];
  }
  vector<vector<int>> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[c[i]].push_back(i);
  }
  SparseTable st(c, [&](int x, int y) {
    return min(x, y);
  });
  vector<pair<int, int>> add;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < (int) pos[i].size() - 1; ++j) {
      int l = pos[i][j];
      int r = pos[i][j + 1];
      if (st.get(l, r) < i) {
        add.emplace_back(l, r);
      } 
    }
  } 
  vector<array<int, 3>> q(m);
  for (int i = 0; i < m; ++i) {
    cin >> q[i][0] >> q[i][1];
    --q[i][0], --q[i][1];
    q[i][2] = i;
  } 
  
  sort(q.begin(), q.end());
  vector<int> ans(m);
  {
    Fenw b(n);
    for (int i = 0; i < n; ++i) {
      if (!pos[i].empty()) {
        b.modify(pos[i][0]);
      }  
    }
    
    int lst = 0;
    for (auto[l, r, id] : q) {
      while (lst < l) {
        b.modify(lst, -1);
        if (pos[c[lst]].back() != lst) {
          b.modify(*lower_bound(pos[c[lst]].begin(), pos[c[lst]].end(), lst + 1));
        }
        ++lst;
      }
      ans[id] += b.get(r);
    }
  }

  {
    sort(add.begin(), add.end());
    Fenw b(n);
    for (auto[foo, r] : add) {
      b.modify(r);
    }
    int lst = 0;
    for (auto[l, r, id] : q) {
      while (lst < (int) add.size() && add[lst].first < l) {
        b.modify(add[lst].second, -1);
        ++lst;      
      }
      ans[id] += b.get(r); 
    }  
  }

  for (int i = 0; i < m; ++i) {
    cout << ans[i] << '\n';
  }
}