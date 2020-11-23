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

  int n, x, y;
  cin >> n >> x >> y;
  int sect = x ^ y;
  
  auto ask = [&](vector<int> a) {
    cout << "? " << (int) a.size() << ' ';
    for (auto el : a) {
      cout << el << ' ';
    }
    cout << endl;
    
    int ver;
    cin >> ver;

    if (ver == 0) {
      // even y, even x
      return 0;
    }
    
    if (ver == x) {
      // even y, odd x
      return 1;
    }

    if (ver == y) {
      // even x, odd y 
      return 2;
    }

    if (ver == sect) {
     // odd y, odd x
      return 3;
    }
    assert(false);
  };


  int can = 0; 
  int diff = 0;
  debug(n);
  for (int bit = 0; bit <= 9; ++bit) {
    debug(bit);
    vector<int> my;
    for (int j = 1; j <= n; ++j) {
      if (j & (1 << bit)) {
        my.push_back(j);
      }
    }
    if (my.empty()) {
      break;
    }
    auto now = ask(my);
    debug(now);
    if (now > 1) {
      can = bit;
      diff |= (1 << bit);
    }
    debug(bit);
  }

  auto take = [&](vector<int> a) {
    int low = 0, high = (int) a.size() - 1;
    while (low < high) {
      int mid = (low + high) >> 1;
      vector<int> cur;
      for (int i = 0; i <= mid; ++i) {
        cur.push_back(a[i]);  
      }
      if (ask(cur) > 1) {
        high = mid;
      } else {
        low = mid + 1;
      }
    }
    return a[low];
  };
  debug(can);
  vector<vector<int>> g(2);
  for (int i = 1; i <= n; ++i) {
    g[bool(i & (1 << can))].push_back(i);
  }
  debug(g);
  int left = take(g[0]);
  int right = left ^ diff;
  if (left > right) {
    swap(left, right);
  }

  cout << "! " << left << ' ' << right << endl;
}