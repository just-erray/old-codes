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

template<typename T, typename F = function<T(const T&, const T&)>> class Bit {
  public:
  vector<T> tree;
  F cal;
  int sz;
  int lb(int x) { return x & -x; }
  void modify(int ind, T val) {
    ++ind;
    while (ind < sz) {
      tree[ind] = cal(tree[ind], val);
      ind += lb(ind);
    }
  }
  Bit(vector<T> v, T uneff, F _cal) : cal(_cal) {
    sz = (int) v.size() + 1;
    tree.resize(sz, uneff);
    for (int i = 0; i < (int) v.size(); ++i) modify(i, v[i]);
  }
  T get(int ind) {
    T res = tree[0];
    while (ind) {
      res = cal(res, tree[ind]);
      ind -= lb(ind);
    }
    return res;
  }
  void clear() {
    fill(tree.begin(), tree.end(), tree[0]);
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  debug(a);
  Bit<int> st(a, 0, [&](int x, int y) {
    return x ^ y;
  });
  Bit<int> first = st;
  int m;
  cin >> m;
  vector<tuple<int, int, int>> q(m);
  vector<int> ans(m);
  for (int i = 0; i < m; ++i) {
    cin >> get<0>(q[i]) >> get<1>(q[i]);
    get<2>(q[i]) = i;
  }
  sort(q.begin(), q.end(), [&](auto x, auto y) {
    return get<1>(x) < get<1>(y);  
  });
  debug(q);
  int lst = 0;
  map<int, int> ind;
  for (auto[l, r, id] : q) {
    --l, --r;
    while (lst <= r) {
      if (ind.count(a[lst])) {
        st.modify(ind[a[lst]], a[lst]);
      }
      ind[a[lst]] = lst;
      ++lst;
    }
    ans[id] = st.get(r + 1) ^ st.get(l) ^ first.get(r + 1) ^ first.get(l);
  }
  for (auto el : ans) {
    cout << el << '\n';
  }
}