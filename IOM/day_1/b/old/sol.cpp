#include<bits/stdc++.h>

using namespace std;

template<typename A, typename B> string to_string(pair<A, B>);
template<typename A, typename B, typename C> string to_string(tuple<A, B, C>);
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D>);

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(char c) {
  return "'"s + c + "'";
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if ((int) res.size() > 1) {
      res += ", ";
    }  
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T v) {
  string res = "{";
  for (const auto& el : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }  
    res += to_string(el);
  }
  res += "}";
  return res;
}


template<typename A, typename B> string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";  
}
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ')';
}
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ", " + to_string(get<3>(t)) + ')';
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << "  " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else 
#define debug(...) void(37)
#endif

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

struct Treap {
  array<Treap*, 2> c;
  int size;
  int left;
  int ind;
  int prio;

  Treap(int _ind) : c({0, 0}), size(1), left(1), ind(_ind), prio(rng()) { }
};

typedef Treap* pt;

int size(pt x) {
  if (x == 0) {
    return 0;
  }
  return x->size;
}

void pull(pt x) {
  x->size = size(x->c[0]) + size(x->c[1]) + 1;
  x->left = x->size - size(x->c[1]);  
}

pt unite(pt x, pt y) {
  if (x == 0) {
    return y;
  }
  
  if (y == 0) {
    return x;
  }

  if (x->ind > y->ind) {
    swap(x, y);
  }
  debug(x->ind, y->ind);

  if (x->prio > y->prio) {
    x->c[1] = y;
    x->c[0] = unite(
    pull(x);
    return x;
  } else {
    y->c[0] = unite(x, y->c[0]);
    pull(y);
    return y;
  }
}


pt erase(pt x, int tar) {
  if (x == 0) {
    return 0;
  }

  if (x->ind == tar) {
    pt res = unite(x->c[0], x->c[1]);  
    pull(res);
    return res;
  }

  if (tar > x->ind) {
    x->c[0] = erase(x->c[0], tar);
  } else {
    x->c[1] = erase(x->c[1], tar);
  }
  pull(x);
  return x;
}

int MEX(pt x, int e) {
  if (x == 0) {
    return -1;
  }
  if (x->left == x->ind + 1 - e) {
    int res = MEX(x->c[1], e + x->left);   
    if (res == -1) {
      return x->ind;
    }
    return res;
  } else {
    return MEX(x->c[0], e);
  }
}

void tour(pt x, int d, vector<pair<int, int>>& res) {
  if (x == 0) {
    return;
  }
  
  tour(x->c[0], d + 1, res);
  res.emplace_back(x->ind, d);
  tour(x->c[1], d + 1, res);
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
  }
  debug(c);
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int x, int y) {
    return c[x] > c[y];
  });


  vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[ord[i]] = i;
  }
  debug(ord, pos);
  vector<pt> g(n);
  multiset<int> ans;
  for (int i = 0; i < n; ++i) {
    g[i] = new Treap(pos[i]);
  }
  
  auto calc = [&](int v, int u) {
    if (v == 0 || u == 0) {
      if (v == 1 || u == 1) {
        return c[ord[0]] + c[ord[1]] + c[ord[2]]; 
      }
      return c[ord[u]] + c[ord[v]] + c[ord[1]];
    }
    return c[ord[u]] + c[ord[v]] + c[ord[0]];
  };

  auto f = [&](int v) {
    int mm = MEX(g[v], 0);
    return calc(pos[v], mm + 1); 
  };

  auto d = [&] {
    #ifdef LOCAL
    for (int i = 0; i < n; ++i) {
      vector<pair<int, int>> res;
      tour(g[i], 0, res);
      int ff = MEX(g[i], 0) + 1;
      debug(i, res, ff);
    }

    #endif
  };
  
  vector<int> cur(n);

  auto add = [&](int t, int v, int u) {
    if (t == 1) {
      ans.erase(cur[v]);
      pt aa = new Treap(pos[u]);
      g[v] = unite(g[v], aa);
      cur[v] = f(v);
      ans.insert(cur[v]);
    } else {
      if (g[v]->size != n) {
        ans.erase(cur[v]);
      }
      g[v] = erase(g[v], pos[u]);
      cur[v] = f(v);
      ans.insert(cur[v]);
    }
  };

  
  while (m--) {
    int x, y;
    cin >> x >> y;
    //add(1, x - 1, y - 1);
    add(1, y - 1, x - 1);
    d();
  }
  /*
  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    add(t, x - 1, y - 1);
    add(t, y - 1, x - 1);
    debug(cur);
    cout << (ans.empty() ? 0 : *prev(ans.end())) << '\n';
  }
  */
}