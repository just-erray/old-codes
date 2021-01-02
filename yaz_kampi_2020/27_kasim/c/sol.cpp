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
#define debug(...) cerr << "\033[" << 1 << "m" << "-> " << "\033[" << 0 << "m", debug_out(3, true, string(#__VA_ARGS__), __VA_ARGS__)
#define here cerr << "-> " << __LINE__ << endl
#else
#define debug(...) void(42)
#define here void(42)
#endif

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count()); 

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  auto ask = [&](int a, int b, int c) {
    cout << "? " << a << ' ' << c << ' ' << b << endl;
    string res;
    cin >> res;
    return (res[0] == 'Y');
  };

  int n, k;
  cin >> n >> k;

  auto Rand = [&](int v = -1) {
    int res;
    do {
      res = uniform_int_distribution<int>(1, n)(rng) ;   
    } while (res == v);
    return res;
  };

  auto isLeaf = [&](int v) {
    int u = Rand(v);
    for (int i = 1; i <= n; ++i) {
      if (i == v || i == u) {
        continue;
      }
      if (ask(i, u, v)) {
        debug(v, "f");
        return false;
      }
    }
    debug(v, "t");
    return true;
  };

  auto findLeaf = [&](int u = -1) {
    int res = -1;
    while (res == -1) {
      int v = Rand(u);
      if (isLeaf(v)) {
        res = v;
      }
    }
    return res;
  };
 
  int need = 0;
  int neg = 1;
  int tn = n;
  while (tn > 0) {
    tn -= neg;
    ++need;
    neg *= k;
  }

  int l1 = findLeaf();
  auto cnt = [&](int x) {
    int cur = 0;
    for (int i = 1; i <= n; ++i) {
      if (i == l1 || i == x) {
        continue;
      }  
      cur += ask(l1, x, i);
    }
    return cur;
  };


  int l2;
  do {
    l2 = findLeaf(l1);
  } while (cnt(l2) != need * 2 - 3);

  

  vector<int> pos;
  for (int i = 1; i <= n; ++i) {
    if (l1 == i || l2 == i) {
      continue;
    } 
    if (ask(l1, l2, i)) {
      pos.push_back(i);
    }
  }
  shuffle(pos.begin(), pos.end(), rng);

  assert((int) pos.size() == need * 2 - 3);

  debug(l1, l2, pos, need);
  int ans = -1;
  for (auto v : pos) {
    if (cnt(v) == need - 2) {
      ans = v;
      break;
    }
  }
  assert(ans != -1);

  cout << "! " << ans << endl;
}                     