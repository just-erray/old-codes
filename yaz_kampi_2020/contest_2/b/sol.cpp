// author: erray
#include<bits/stdc++.h>
#undef DEBUG
 
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
  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<string> mat(n);
    for (int i = 0; i < n; ++i) {
      cin >> mat[i];
    }
    vector<vector<bool>> vis(n, vector<bool>(m));
    vector<vector<int>> sp(n, vector<int>(m, (int) 1e7));
    sp[0][0] = 0;
    deque<pair<int, int>> que;
    que.emplace_back(0, 0);
    const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    while (!que.empty()) {
      debug(que);
      auto[x, y] = que.front();
      que.pop_front();
      debug(sp[x][y], mat[x][y]);
      if (vis[x][y]) {
        continue;
      }
      vis[x][y] = true;

      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        //debug(nx, ny);
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
          continue;
        }
        if (vis[nx][ny]) {
          continue;
        }  
        //vis[nx][ny] = true;
        //debug(x, y, nx, ny, mat[x][y], mat[nx][ny]);
        if (mat[x][y] == mat[nx][ny]) {
          que.emplace_front(nx, ny);
          sp[nx][ny] = min(sp[x][y], sp[nx][ny]); 
        } else {
          que.emplace_back(nx, ny);
          sp[nx][ny] = min(sp[x][y] + 1, sp[nx][ny]);

        }
      }
    }
    debug(sp);
    /*
    debug(sp);
    debug(from);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (from[i][j].first != i) {
          cout << (from[i][j].first > i ? 'D' : 'U');
        } else {
          cout << (from[i][j].second > j ? 'R' : 'L');          
        }
        cout << ' ';
      }
      cout << '\n';
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << sp[i][j] << ' ';
        cout << ' ';
      }
      cout << '\n';
    }
    */
    cout << sp[n - 1][m - 1] << '\n';
  }
}