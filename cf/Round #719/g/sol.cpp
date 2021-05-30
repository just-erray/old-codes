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
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, w;
  cin >> n >> m >> w;
  vector<vector<int>> mat(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }


  struct pq_el {
    int v;
    long long cost;
    bool operator<(const pq_el& ot) const {
      return cost > ot.cost;
    }
  };

  auto Hash = [&](int x, int y) {
    return x * m + y;
  };

  auto Rehash = [&](int x) {
    return make_pair(x / m, x % m);
  };

  set<pair<int, int>> available;
  long long closest = -1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mat[i][j] > 0) {
        available.emplace(mat[i][j], Hash(i, j));
      }
    }
  }
  debug(available);

  const int dx[] = {1, -1, 0, 0,}, dy[] = {0, 0, 1, -1};
  priority_queue<pq_el> pq;
  pq.push(pq_el{0, 0});
  pq.push(pq_el{0, LLONG_MAX});
  vector<bool> vis(n * m);
  vector<long long> sp(n * m);
  while (!pq.empty()) {
    auto[v, cost] = pq.top();
    bool skip = false;
    if (closest != -1 && !available.empty() && available.begin()->first + closest <= cost) {
      skip = true;
      pq.push(pq_el{available.begin()->second, available.begin()->first + closest});
      available.erase(available.begin());
    }
    debug(closest);
    debug(v, cost, skip);
    if (skip) {
      continue;
    }
    
    auto[x, y] = Rehash(v);
    debug(x, y);
    pq.pop();
    if (vis[v]) {
      continue;
    }
    sp[v] = cost;
    vis[v] = true;
    if (mat[x][y] > 0) {
      if (closest == -1) {
        closest = LLONG_MAX;
      }
      closest = min(closest, cost + mat[x][y]);  
    }
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d];
      int ny = y + dy[d];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m || mat[nx][ny] == -1) {
        continue;
      } 
      pq.push(pq_el{Hash(nx, ny), cost + w});
    }
  }

  cout << (vis.back() ? sp.back() : -1LL) << '\n';
}