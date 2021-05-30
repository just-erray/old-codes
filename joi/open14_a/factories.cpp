#include<bits/stdc++.h>
#include "factories.h"
using namespace std;
 template<typename A, typename B> string to_string(pair<A, B> p);
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t);
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t);

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(char c) {
  return string("'") + c + "'";
}

string to_string(const char* c) {
  return to_string(string(c));
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

template<size_t T> string to_string(bitset<T> bs) {
  return bs.to_string();
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < int(v.size()); ++i) {
    if (i > 0) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& e : v) {
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(e);
  }
  res += "}";
  return res;
}

template<typename A, typename B> string to_string(pair<A, B> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + '}';
}
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ", " + to_string(get<3>(t)) + '}';   
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << "  " << to_string(H);
  debug_out(T...);
}

#ifdef DEBUG 
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) void(37)
#endif
template<typename T, typename F = function<T(const T&, const T&)>> struct SparseTable {
  int sz, lg;
  vector<vector<T>> table;
  F cal;
  SparseTable() { }
  SparseTable(vector<T> v, F _cal) : cal(_cal) {
    sz = (int) v.size();
    lg = 32 - __builtin_clz(sz);
    table.resize(lg);
    table[0] = v;
    for (int i = 1; i < lg; ++i) {
      table[i].resize(sz - (1 << i) + 1);
      assert(sz - (1 << i) + 1 >= 0);
      for (int j = 0; j < (int) table[i].size(); ++j) {
        table[i][j] = cal(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  T get(int l, int r) {
    assert(l >= 0 && r < sz && l <= r);
    int clg = 31 - __builtin_clz(r - l + 1);
    return cal(table[clg][l], table[clg][r - (1 << clg) + 1]);
  }
};

vector<vector<int>> pars;
SparseTable<int> st;
vector<int> tour;
vector<int> stime;
vector<int> etime;
vector<long long> d;
vector<vector<long long>> sp;   
vector<long long> best;
int Lca (int x, int y) {
  if (stime[x] > stime[y]) {
    swap(x, y);
  }
  if (etime[x] >= etime[y]) {
    return x;
  }
  return st.get(etime[x], stime[y]);
}

long long Sp(int x, int y) {
  return d[x] + d[y] - 2 * d[Lca(x, y)];
}


const long long inf = (long long) 1e17;
void Init(int n, int a[], int b[], int ws[]) {
  best.resize(n, inf);
  debug("hi");
  vector<vector<pair<int, int>>> wg(n);
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    wg[a[i]].emplace_back(b[i], ws[i]);
    wg[b[i]].emplace_back(a[i], ws[i]);
    g[a[i]].push_back(b[i]);
    g[b[i]].push_back(a[i]);
  }
  

  d.resize(n);
  stime.resize(n);
  etime.resize(n);
  vector<int> size(n, 1);
  function<void(int, int)> Pre_dfs = [&](int v, int pr) {      
    debug(v, pr);
    stime[v] = etime[v] = int(tour.size());
    tour.push_back(v);
    for (auto e : wg[v]) {
      int u, w;
      tie(u, w) = e;
      if (u == pr) {
        continue;
      }
      d[u] = d[v] + w;
      Pre_dfs(u, v);
      size[v] += size[u];
      etime[v] = int(tour.size());
      tour.push_back(v);
    }  
  };
  Pre_dfs(0, -1);
  st = SparseTable<int>(tour, [&](int x, int y) {
    return (d[x] < d[y] ? x : y);
  });
  debug(d, tour, stime, etime); 
  debug(size);


  vector<int> par(n);
  function<void(int, int)> Dfs = [&](int v, int pr) {
    if (size[v] == 0) {
      return;
    }
    int no = -1;
    debug(v, pr);
    for (auto u : g[v]) {
      if (size[u] > size[v] / 2) {
        assert(no == -1);
        no = u;
      }
    }
    if (no == -1) {
      par[v] = pr;
      size[v] = 0;
      debug("look at me, I'm the root now", v);
      for (auto u : g[v]) {
        Dfs(u, v);
      }
    } else {
      size[v] -= size[no];
      size[no] += size[v];
      debug(size[v], size[no]);
      Dfs(no, pr);
    }
  }; 
  Dfs(0, -1);
  debug(par);
  pars.resize(n);
  sp.resize(n);
  for (int i = 0; i < n; ++i) {
    int me = i;
    while (me != -1) {
      pars[i].push_back(me);
      sp[i].push_back(Sp(i, me));
      me = par[me];
    }
  }
  debug(pars);
  debug(sp);
  debug("Init end /*--------------------------------------------------------------------------*/");
}

long long Query(int s, int x[], int t, int y[]) {
  for (int j = 0; j < s; ++j) {
    int v = x[j];
    for (int i = 0; i < int(pars[v].size()); ++i) {
      int u = pars[v][i];
      best[u] = min(best[u], sp[v][i]);
    }
  }
  long long res = inf;
  for (int j = 0; j < t; ++j) {
    int v = y[j];
    for (int i = 0; i < int(pars[v].size()); ++i) {
      int u = pars[v][i];
      res = min(res, best[u] + sp[v][i]);
    }
  }
  
  for (int j = 0; j < s; ++j) {
    int v = x[j];
    for (int i = 0; i < int(pars[v].size()); ++i) {
      int u = pars[v][i];
      best[u] = inf;
    }
  }
  return res;
}
