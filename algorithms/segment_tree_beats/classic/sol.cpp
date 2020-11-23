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

struct SegTree {
  struct node {
    int mx = INT_MAX, mx2 = 0, lazy = INT_MAX, cnt = 1;
    long long sum = INT_MAX;
    void modify(int x) {
      if (x >= mx) {
        return;
      }
      assert(lazy >= x);
      lazy = x;
      sum -= 1LL * cnt * (mx - x);
      mx = x;
    }
  };
  node emp;
  int n;
  vector<node> tree;

  node unite(const node& x, const node& y) {
    node res;
    res.sum = x.sum + y.sum;
    res.mx = max(x.mx, y.mx); 
    res.cnt = x.cnt * (x.mx == res.mx) + y.cnt * (y.mx == res.mx);
    res.mx2 = max({(res.mx != x.mx) * x.mx, x.mx2, (res.mx != y.mx) * y.mx, y.mx2});
    return res;
  }

  void push(int v, int rv) {
    if (tree[v].lazy != emp.lazy) {
      tree[v + 1].modify(tree[v].lazy);
      tree[rv].modify(tree[v].lazy);
    }        
    tree[v].lazy = emp.lazy;
  }

  void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]);
  }

  void modify(int v, int l, int r, int ll, int rr, int val) {
    if (tree[v].mx <= val) {
      return;
    }  

    if (l >= ll && rr >= r && tree[v].mx2 <= val) {
      tree[v].modify(val);
      return;
    }
    
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, rv);
    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, val);
    }
    if (mid < rr) {
      modify(rv, mid + 1, r, ll, rr, val);
    }

    pull(v, rv);
  }

  long long get(int v, int l, int r, int ll, int rr) {
    if (l >= ll && rr >= r) {
      return tree[v].sum;
    }  
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, rv);

    long long res = 0;
    if (mid >= ll) {
      res += get(v + 1, l, mid, ll, rr);
    }
    if (mid < rr) {
      res += get(rv, mid + 1, r, ll, rr);
    }
    return res;
  }

  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }

  void modify(int ll, int rr, int val) {
    assert(ll <= rr && ll >= 0 && rr < n);
    modify(0, 0, n - 1, ll, rr, val);
  }

  long long get(int ll, int rr) {
    assert(ll <= rr && ll >= 0 && rr < n);
    return get(0, 0, n - 1, ll, rr);  
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  SegTree st(n);

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    st.modify(i, i, x);
  }

  int q;
  cin >> q;
  while (q--) {
    int type, l, r;
    cin >> type >> l >> r;
    --l, --r;
    if (type) {
      int val;
      cin >> val;
      st.modify(l, r, val);
    } else {
      cout << st.get(l, r) << endl;
    }
  }
}