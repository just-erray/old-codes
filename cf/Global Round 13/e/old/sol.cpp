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

vector<vector<int>> rg;
vector<int> fib(2, 1);

int dfs(int v, const set<int>& border, vector<int>& be, const int& Find) {
  int res = 1;
  for (auto u : rg[v]) {
    if (border.count(u)) {
      continue;
    }
    res += dfs(u, border, be, Find);
  }
  debug(v, res);
  if (res == Find) {
    be.push_back(v);
  }
  return res;                   
}


void divide(int v, const set<int>& border, set<int>& new_border) {
  if (border.count(v)) {
    new_border.insert(v);
    return;
  }

  for (auto u : rg[v]) {
    divide(u, border, new_border);
  }
}
 
bool solve(int v, set<int> border, int size) {
  debug(v, border, size);
  if (size <= 3) {
    return true;
  }   

  if (*lower_bound(fib.begin(), fib.end(), size) != size) {
    return false;
  }

  vector<int> add;
  int Find = *prev(prev(lower_bound(fib.begin(), fib.end(), size)));
  int Bef = *prev(prev(prev(lower_bound(fib.begin(), fib.end(), size))));
  dfs(v, border, add, Find);
  if ((int) add.size() < 2) {
    if (add.empty()) {
      return false;
    } 
    border.insert(add[0]);
    dfs(v, border, add, Bef);
    border.erase(add[0]);
    if ((int) add.size() < 2) {
      return false;
    }

    while ((int) add.size() > 2) {
       add.pop_back();
    }
    debug(add);
    set<int> f1; divide(add[0], border, f1);
    border.insert(add[0]);
    set<int> f2; divide(add[1], border, f2);
    debug(f1, f2);
    debug(border);
    for (auto e : f1) {
      border.erase(e);
    }
    debug(border);
    for (auto e : f2) {
      border.erase(e);
    }

    debug(border);
    border.insert(add.begin(), add.end());
    return solve(add[0], f1, Find) && solve(add[1], f2, Bef) && solve(v, border, size - Find - Find);  

  } else {
    assert((int) add.size() <= 2);
    set<int> f1; divide(add[0], border, f1);
    set<int> f2; divide(add[1], border, f2);
    for (auto e : f1) {
      border.erase(e);
    }
    debug(border);
    for (auto e : f2) {
      border.erase(e);
    }

    border.insert(add.begin(), add.end());
    return solve(add[0], f1, Find) && solve(add[1], f2, Find) && solve(v, border, size - Find - Find);  
  }
} 

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  while (fib.back() < n) {
    fib.push_back(fib[(int) fib.size() - 2] + fib.back());
  }

  function<void(int, int)> Dfs = [&](int v, int pr) {
    for (auto u : g[v]) {
      if (u == pr) {
        continue;
      }
      rg[v].push_back(u);
      Dfs(u, v);
    }
  };

  rg.resize(n);
  Dfs(0, -1);

  cout << (n == fib.back() && solve(0, set<int>(), n) ? "YES" : "NO");
 
}
