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


struct SegTree {
  struct node {
    //variables default values should be uneffective     
    long long v = 0;
    long long tag = 0;
    void modify(int l, int r, long long x) {
      v += x;
      tag += x;
    }

    int get (int l, int r) {
      //..
      return l + r;
    }
  };

  node emp;
  
  node unite(const node& x, const node& y) {
    node res;
    res.v = x.v + y.v;
    return res;
  }
  
  inline void push(int v, int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    if (tree[v].tag != emp.tag) {
      tree[rv].modify(mid + 1, r, tree[v].tag); 
      tree[v + 1].modify(l, mid, tree[v].tag); 
    }
    tree[v].tag = emp.tag;
  }
  
  /*----------------------------------Only up needs to change----------------------------------------*/

  inline void pull(int v, int rv) {
    tree[v] = unite(tree[v + 1], tree[rv]);
  }

  int n;
  vector<node> tree;

  template<typename T> void build(int v, int l, int r, const vector<T> vv) {     
    if (l == r) {
      tree[v].modify(l, r, vv[l]);
      return;
    }    
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    build(v + 1, l, mid, vv);
    build(rv, mid + 1, r, vv);
    pull(v, rv);
  }

  node get(int v, int l, int r, int ll, int rr) {
    if (l >= ll && rr >= r) {   
      return tree[v]; 
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    if (mid >= ll && mid < rr) {
      return unite(get(v + 1, l, mid, ll, rr), get(rv, mid + 1, r, ll, rr));          
    } 
    if (mid >= ll) {
      return get(v + 1, l, mid, ll, rr);    
    }
    return get(rv, mid + 1, r, ll, rr);
  }

  template<typename R, typename... T> R get(int v, int l, int r, int ll, int rr, function<R(const R&, const R&)> f, const T&... t) {
    if (l >= ll && rr >= r) {
      return tree[v].get(l, r, t...); 
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    if (mid >= ll && mid < rr) {
      return f(get(v + 1, l, mid, ll, rr, t...), get(rv, mid + 1, r, ll, rr, t...));          
    } 
    if (mid >= ll) {
      return get(v + 1, l, mid, ll, rr, t...);    
    }
    return get(rv, mid + 1, r, ll, rr, t...);
    
  }

  template<typename... T> void modify(int v, int l, int r, int ll, int rr, const T&... t) {
    if (l >= ll && rr >= r) {
      tree[v].modify(l, r, t...);
      return;      
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);
 
    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, t...);    
    }
    if (mid < rr) {
      modify(rv, mid + 1, r, ll, rr, t...);
    }
    pull(v, rv); 
  }

  template<typename... T> void set_modify(int v, int l, int r, int tar, const T&... t) {
    if (l == r) {
      tree[v] = emp;
      tree[v].modify(l, r, t...);
      return;      
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);
 
    if (mid >= tar) {
      set_modify(v + 1, l, mid, tar, t...);    
    }
    if (mid < tar) {
      set_modify(rv, mid + 1, r, tar, t...);
    }
    pull(v, rv); 
  }

  int find_first_exact(int v, int l, int r, const function<bool(const node&)> f) {
    if (!f(tree[v])) return -1;
    if (l == r) {
      return l;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    int res = -1;
    if (f(tree[v + 1])) {
      res = find_first_exact(v + 1, l, mid, f);
    } else {
      res = find_first_exact(rv, mid + 1, r, f);
    }
    assert(res != -1);
    return res;
  }

  int find_last_exact(int v, int l, int r, const function<bool(const node&)> f) {
    if (!f(tree[v])) return -1;
    if (l == r) {
      return l;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    int res = -1;
    if (f(tree[rv])) {
      res = find_last_exact(rv, mid + 1, r, f);
    } else {
      res = find_last_exact(v + 1, l, mid, f);
    }
    assert(res != -1);
    return res;
  }

  int find_first(int v, int l, int r, int ll, int rr, const function<bool(const node&)> f) {
    if (l >= ll && rr >= r) {
      return find_first_exact(v, l, r, f);
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    int res = -1;
    if (mid >= ll) {
      res = find_first(v + 1, l, mid, ll, rr, f);
    }
    if (res == -1 && mid < rr) {
      res = find_first(rv, mid + 1, r, ll, rr, f);
    }
    return res;
  }

  int find_last(int v, int l, int r, int ll, int rr, const function<bool(const node&)> f) {
    if (l > rr || r < ll) {
      return -1;
    }
    if (l >= ll && rr >= r) {
      return find_last_exact(v, l, r, f);
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    int res = -1;
    if (mid < rr) {
      res = find_last(rv, mid + 1, r, ll, rr, f);
    }
    if (res == -1 && mid >= ll) {
      res = find_last(v + 1, l, mid, ll, rr, f);
    }
    return res;
  }

  /*==========================================================================*/


  SegTree(int _n) : n(_n) {
    assert(n > 0);
    tree.resize(n * 2 - 1);
  }

  template<typename T> SegTree(vector<T> v) : n((int) v.size()) {
    tree.resize(n * 2 - 1);
    build(0, 0, n - 1, v);        
  }

  node get(int ind) {
    assert(ind >= 0 && ind < n);
    return get(0, 0, n - 1, ind, ind);
  }
  
  node get(int l, int r) {  
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);  
    return get(0, 0, n - 1, l, r);
  }

  template<typename R, typename... T> R get(int l, int r, function<R(const R&, const R&)> f, T... t) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);  
    return get<R>(0, 0, n - 1, l, r, f, t...);
  }

  template<typename... T> void modify(int l, int r, T... t) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);
    modify(0, 0, n - 1, l, r, t...);    
  }

  template<typename... T> void set_modify(int ind, T... t) {
    assert(ind >= 0 && ind < n);
    set_modify(0, 0, n - 1, ind, t...);    
  }
  
  int find_first(int l, int r, const function<bool(const node&)> f) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);  
    return find_first(0, 0, n - 1, l, r, f);    
  }

  int find_last(int l, int r, const function<bool(const node&)> f) {
    assert(l >= 0 && l < n && r >= 0 && r < n && r >= l);  
    return find_last(0, 0, n - 1, l, r, f);    
  }
  
  int find_first(const function<bool(const node&)> f) {
    return find_first(0, 0, n - 1, 0, n - 1, f);    
  }

  int find_last(const function<bool(const node&)> f) {
    return find_last(0, 0, n - 1, 0, n - 1, f);    
  }  
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
      int x;
      cin >> x;
      --x;
      g[x].push_back(i);
    }

    vector<vector<int>> bg(n);
    vector<int> par(n, -1);
    for (int i = 1; i < n; ++i) {
      int x;
      cin >> x;
      --x;
      bg[x].push_back(x);
      par[i] = x;
    }

    vector<int> tin(n);
    vector<int> tout(n);
    vector<int> d(n);
    int t = 0;
    function<void(int)> Bdfs = [&](int v) {
      tin[v] = t++;
      for (auto u : bg[v]) {
        d[u] = d[v] + 1;
        Bdfs(u);
      }
      tout[v] = t++;
    };
    Bdfs(0);
    const int T = 2 * n;
    debug(tin);
    debug(tout);
    SegTree in(T);
    SegTree out(T);
    SegTree act_in(T);
    SegTree act_out(T);
    struct Move {
      int in;
      int out;
      bool changed = false;
    };


    vector<Move> moves;
    int size = 0;

    auto add = [&](int x) {
      in.modify(0, tin[x], +1);
      out.modify(0, tin[x], +1);
      act_in.modify(0, tin[x], +1);
      act_out.modify(0, tin[x], +1);    
    };

    auto erase = [&](int x) {
      in.modify(0, tin[x], -1);
      out.modify(0, tin[x], -1);      
      act_in.modify(0, tin[x], -1);
      act_out.modify(0, tin[x], -1);    
    };

    auto Get = [&](int v) {
      return in.get(v).v - out.get(v).v;
    };


    auto Add = [&](int x) {
      if (Get(x)) {
        moves.push_back(Move{0, 0, false});
        return;
      }     

      int low = 0, high = d[x] - 1;
      while (low < high) {
        
      }
      int bad = (Act(Up(x, low)) ? Up(x, low) : -1);
      if (bad != -1) {
        erase(bad);
      }
      add(x);
      moves.push_back(Move{x, bad, true});
    };

    auto Rollback = [&] {
      if (moves.back().changed) {
        erase(moves.back().in);
        if (moves.back().out != -1) {
          add(moves.back().out);
        }
      }
      moves.pop_back();  
    };

    int ans = 0;
    function<void(int)> Dfs = [&](int v) {
      Add(v); 
      ans = max(ans, size);
      for (auto u : g[v]) {
        Dfs(u);
      }
      Rollback();
    };
    Dfs(0);
    cout << ans << '\n';
  }
}