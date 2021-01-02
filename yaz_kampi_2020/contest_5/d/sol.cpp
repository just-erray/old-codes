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

struct fenw {
  vector<int> tree;
  int n;

  int lb(int x) {
    return x & -x;
  }

  void modify(int ind, int val) {
    ++ind;
    while (ind <= n) {
      tree[ind] += val;
      ind += lb(ind);
    }
  }
  
  fenw(int _n) : n(_n) {
    tree.resize(n + 1);
    for (int i = 0; i < n; ++i) {
      modify(i, 1);
    }
  }

  int get(int ind) {
    ++ind;
    int res = 0;
    while (ind) {
      res += tree[ind];
      ind -= lb(ind);
    }
    return res;
  }
  
  pair<int, int> next(int ind) {
    pair<int, int> res;
    int st = get(ind);
    {
      int low = -1, high = ind - 1;
      while (low < high) {
        int mid = (low + high) >> 1;
        if (get(mid) == st) {
          high = mid;
        } else {
          low = mid + 1;
        }
      }
      res.first = low;
    }
    {
      int low = ind + 1, high = n - 1;
      while (low < high) {
        int mid = 1 + ((low + high) >> 1);
        if (get(mid) == st) {
          low = mid;
        } else {
          high = mid - 1;
        }
      }
      res.second = low + 1;
    }
    debug(res);
    return res;
  }

};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  string s;
  cin >> n >> s;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  fenw bit(n);
  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
  for (int i = 1; i < n; ++i) {
    if (s[i] != s[i - 1]) {
      pq.emplace(abs(a[i] - a[i - 1]), i - 1, i);
    }    
  }

  vector<pair<int, int>> ord;
  auto range = [&](int l, int r) {
    return l >= 0 && r < n;
  };

  while (!pq.empty()) {
    auto[cost, l, r] = pq.top();
    pq.pop();
    debug(l, r);
    if (bit.get(l) - bit.get(l - 1) == 0 || bit.get(r) - bit.get(r - 1) == 0) {
      continue;
    }
    ord.emplace_back(l, r);    
    bit.modify(l, -1);
    bit.modify(r, -1);               
    auto[nl, nr] = bit.next(l);
    if (range(nl, nr) && s[nl] != s[nr]) {
      pq.emplace(abs(a[nl] - a[nr]), nl, nr);
    }
  }
  cout << (int) ord.size() << '\n';
  for (auto[l, r] : ord) {
    cout << min(l, r) + 1 << ' ' << max(r, l) + 1 << '\n';
  }
}               