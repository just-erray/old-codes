// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T, typename F> string to_string(pair<T, F> p);
template<typename T, typename F, typename Tr> string to_string(tuple<T, F, Tr> p);
template<typename T, typename F, typename Tr, typename Th> string to_string(tuple<T, F, Tr, Th> p);
string to_string(string s) {
  return '"' + s + '"';
}
string to_string(char c) {
  return (string) "'" + c + "'";
}
string to_string(const char* p) {
  return to_string((string) p);
}
string to_string(bool B) {
  return (B ? "true" : "false");
}
string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if ((int) res.size() > 1) res += ", ";
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
template<size_t T> string to_string(bitset<T> bs) {
  return bs.to_string();
}
template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& el : v) {
    if ((int) res.size() > 1) res += ", ";
    res += to_string(el);
  }
  res += "}";
  return res;
}
template<typename T, typename F> string to_string(pair<T, F> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename T, typename F, typename Tr> string to_string(tuple<T, F, Tr> p) {
  return '(' + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ')';
}
template<typename T, typename F, typename Tr, typename Th> string to_string(tuple<T, F, Tr, Th> p) {
    return '(' + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ')';
}
void debug_out() {
  cerr << endl;
}
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" , debug_out(__VA_ARGS__)
#else
#define debug(...) (void) 37
#endif

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

class Treap {
  public:
  int ind, sz, prio;
  vector<Treap*> c;

  Treap(int _ind) : ind(_ind) {
    sz = 1;
    prio = (int) rng();
    c = {NULL, NULL};
  }
};

typedef Treap* pt;

int size(pt t) {
  return (t ? t->sz : 0);
}

void re(pt t) {
  if (!t) {
    return;
  }
  t->sz = 1 + size(t->c[0]) + size(t->c[1]);
}

pt unite(pt l, pt r) {
  if (!l) {
    return r;
  }
  if (!r) {
    return l;
  }
  if (l->prio > r->prio) {
    l->c[1] = unite(l->c[1], r);
    re(l);    
    return l;
  } else {
    r->c[0] = unite(l, r->c[0]);
    re(r);
    return r;
  }
}

pair<pt, pt> split(pt t, int v) {
  if (!t) { 
    return make_pair(t, t);
  }
  debug(v, size(t), t->ind);  
  assert(size(t) >= v);
  if (size(t->c[0]) >= v) {
    auto res = split(t->c[0], v);
    t->c[0] = res.second;
    re(t);
    debug(t->ind, t->sz);
    return make_pair(res.first, t);
  } else {
    auto res = split(t->c[1], v - size(t->c[0]) - 1);    
    t->c[1] = res.first;
    re(t);
    debug(t->ind, t->sz);
    return make_pair(t, res.second);
  }
}

void tour(pt t, vector<int>& res) {
  if (!t) {
    return;
  }
  tour(t->c[0], res);
  res.push_back(t->ind); 
  tour(t->c[1], res);
}
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  pt root = new Treap(0);
  for (int i = 1; i < n; ++i) {
    pt tmp = new Treap(i);
    root = unite(root, tmp);
  }

  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    if (a >= b) {
      continue;
    }
    int sz = min(b - a, n - b);
    assert(sz);
    debug(sz);
    vector<pt> con(4);
    tie(con[0], root) = split(root, a);
    debug("Pass");
    tie(con[1], root) = split(root, sz);
    debug("Pass");
    debug(root->ind);
    tie(con[2], root) = split(root, b - a - sz);
    debug("Pass");
    tie(con[3], root) = split(root, sz);
    root = unite(con[1], root);
    root = unite(con[2], root);
    root = unite(con[3], root);
    root = unite(con[0], root);
  }

  vector<int> res;
  tour(root, res);
  for (auto el : res) {
    cout << el + 1 << ' ';
  }
  cout << '\n';
}