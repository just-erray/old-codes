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


bool add(int x, int y, vector<pair<int, int>>& res, vector<string>& mat) {
  assert(mat[x][y] != 'D' && mat[x][y] != 'R');

  if (mat[x][y] == 'L') {
    if (mat[x + 1][y] != 'L') {
      return false;
    }      
    mat[x][y] = 'U';
    mat[x][y + 1] = 'U';
    mat[x + 1][y] = 'D';
    mat[x + 1][y + 1] = 'D';
  } else {
    if (mat[x][y + 1] != 'U') {
      return false;  
    }
    mat[x][y] = 'L';
    mat[x + 1][y] = 'L';
    mat[x][y + 1] = 'R';
    mat[x + 1][y + 1] = 'R';
  }
  res.emplace_back(x, y);
  return true;
}   

void solve(int x, int y, vector<pair<int, int>>& res, vector<string>& mat) {
  if (!add(x, y, res, mat)) {
    if (mat[x][y] == 'L') {
      solve(x + 1, y, res, mat);
    } else {
      solve(x, y + 1, res, mat);
    }
    assert(add(x, y, res, mat));
  }
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> tar(n), cur(n);
  for (int i = 0; i < n; ++i) {
    cin >> cur[i];
  }

  for (int i = 0; i < n; ++i) {
    cin >> tar[i];
  }

  vector<pair<int ,int>> l, r;
  if (n % 2 == 0) {
    for (int i = 0; i < n; i += 2) {
      for (int j = 0; j < m; ++j) {
        if (cur[i][j] == 'L') {
          solve(i, j, l, cur);
        }   
      }
    }
    for (int i = 0; i < n; i += 2) {
      for (int j = 0; j < m; ++j) {
        if (tar[i][j] == 'L') {
          solve(i, j, r, tar);
        }   
      }
    }
  } else {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; j += 2) {
        if (cur[i][j] == 'U') {
          solve(i, j, l, cur);
        }   
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; j += 2) {
        if (tar[i][j] == 'U') {
          solve(i, j, r, tar);
        }   
      }
    }
  }
  l.insert(l.end(), r.rbegin(), r.rend());
  if ((int) l.size() > (int) 1e5) {
    cout << "BRUH";
  }
  cout << (int) l.size() << '\n';
  for (auto[x, y] : l) {
    cout << x + 1 << ' ' << y + 1 << '\n';
  }
}