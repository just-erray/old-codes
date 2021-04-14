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
  auto Hash = [&](string s) {
    long long res = 0;
    long long base = 1;
    for (char c : s) {
      res += base * (c - 'a' + 1);
      base *= 27;
    }
    return res;
  };

  int n, k;
  cin >> k >> n;
  vector<long long> a(n);
  vector<string> aa(n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;        
    aa[i] = s;
    a[i] = Hash(s);
  }
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](auto x, auto y) {
    return aa[x] < aa[y];
  });


  vector<int> forder(n);
  for (int i = 0; i < n; ++i) {
    forder[order[i]] = i;
  }
  map<long long, int> ind;
  for (int i = 0; i < n; ++i) {
    ind[a[i]] = i;
  }
  
  vector<string> ans(n, string(n, '?'));
  auto Add = [&](int x, int y) {
    debug(x, y);
    assert(ans[x][y] != '1');
    ans[x][y] = '0';
    ans[y][x] = '1';
  };
  
  vector<vector<int>> ord(k, vector<int>(n));
  for (int j = 0; j < k; ++j) {
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      ord[j][i] = ind[Hash(s)];
    }
  }

  debug(ord);
  debug(order);

  for (auto e : ord) {
    for (int i = 0; i < n; ++i) {
      bool ok = false;
      for (int j = i + 1; j < n; ++j) {
        ok |= (forder[e[j]] < forder[e[j - 1]]);
        if (ok) {
          Add(e[i], e[j]);
        }
      }
    }
    here;
  }

  for (int len = 1; len < n; ++len) {
    for (int i = 0; i < n - len; ++i) {
      int r = i + len;
      for (int f = i + 1; f < r; ++f) {
        if (ans[i][f] == ans[f][r] && ans[i][f] != '?') {
          ans[i][r] = ans[i][f];
          ans[r][i] = ((ans[i][f] - '0') ^ 1) + '0';
        }
      }
    }
  }
     
  for (int i = 0; i < n; ++i) {
    ans[i][i] = 'B';
    cout << ans[i] << '\n';
  }
}