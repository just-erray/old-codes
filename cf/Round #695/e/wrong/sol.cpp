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

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  
  {
    vector<int> temp = a;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());

    for (int i = 0; i < n; ++i) {
      a[i] = lower_bound(temp.begin(), temp.end(), a[i]) - temp.begin();
    }
  }

  vector<vector<int>> col(n);
  int p = -1;    

  for (int i = 0; i < n; ++i) {
    col[a[i]].push_back(i);
    if ((int) col[a[i]].size() == 2) {
      p = a[i];  
    }

    if ((int) col[a[i]].size() > 2) {
      return cout << 0, 0;
    }
  }

  if (p == -1) {
    return cout << n, 0;
  }

  vector<int> path = {col[p][0]};
  function<bool(int, int)> dfs = [&](int v, int pr) {
    if (v == col[p][1]) {
      return true;
    } 

    for (auto u : g[v]) {
      if (u == pr) {
        continue;
      }
      
      if (dfs(u, v)) {
        path.push_back(u);
        return true;
      }
    }

    return false;
  };

  dfs(col[p][0], -1);
  
  function<void(int, int, vector<int>&)> Dfs = [&](int v, int pr, vector<int>& x) {
    for (auto u : g[v]) {
      if (u == pr) {
        continue;
      }

      if ((int) col[u].size() == 2) x.push_back(u);
      Dfs(u, v, x);
    }
  };

  vector<int> start, end;
  Dfs(path[0], path[1], start);
  Dfs(path.back(), path[(int) path.size() - 2], end);
  path.erase(path.begin());
  path.pop_back();
  debug(path);
  
  const int N = (int) path.size();
  vector<vector<int>> pos(n);
  for (int i = 0; i < N; ++i) {
    pos[a[path[i]]].push_back(i);
  }

  vector<int> where(n);
  for (auto e : start) {
    where[a[e]] += 1;
  }

  for (auto e : end) {
    where[a[e]] += 2;
  }
  
  vector<int> add(N);
  int need = 0;
  for (int i = 0; i < n; ++i) {
    if ((int) col[i].size() == 2 && i != p) {
      if ((int) pos[i].size() == 0) {
        if (where[i] != 3) {
          cerr << "end\n";
          cout << 0;
          return 0;
        }

        ++add[0];
        continue;
      }
      ++need;

      if ((int) pos[i].size() == 1) {
        if (where[i] == 1) {
          ++add[0];
          --add[pos[i][0]];
        } else {
          assert(where[i] == 2);
          ++pos[i][1];
        }   
      } else {
        add[pos[i][0] + 1]++;
        add[pos[i][1]]--;
      }
    }
  }

  int cur = 0;
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    cur += add[i];
    ans += (cur == need);
  }
  
  cout << ans << '\n';
}