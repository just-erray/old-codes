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
  int ind, prio, size = 1;
  vector<Treap*> kids;

  Treap(int _ind) : ind(_ind) {
    kids = {NULL, NULL};
    prio = (int) rng();
    debug(ind, prio);
  }
};

typedef Treap* pt;

bool n(pt p) {
  return (p == NULL);
}

int size(pt t) {
  if (n(t)) {
    return 0;
  }
  return t->size;
}

void calc(pt p) {
  p->size = 1;
  for (int i = 0; i < 2; ++i) {
    if (!n(p->kids[i])) {
      p->size += p->kids[i]->size; 
    }
  }
}

pt unite(pt l, pt r) {
  if (n(l)) {
    debug(r->ind);
    return r;  
  }  
  
  if (n(r)) {
    debug(l->ind);
    return l;  
  }
  debug(l->ind, r->ind);
  pt res;
  if (l->prio < r->prio) {
    debug("LEFT");
    l->kids[1] = unite(l->kids[1], r);
    res = l;
  } else {
    debug("RIGHT");
    r->kids[0] = unite(l, r->kids[0]); 
    res = r;
  }
  calc(res);
  return res;
}

pair<pt, pt> split(pt t, int v) {
  if (n(t)) {
    return make_pair(t, t);
  }  
  assert(size(t) > v);
  pair<pt, pt> r;
  if (size(t->kids[0]) >= v) {
    auto res = split(t->kids[1], v);
    t->kids[0] = res.first;
    calc(t);
    r = make_pair(res.first, t);
  } else {
    auto res = split(t->kids[1], v - size(t->kids[0]) - 1);
    t->kids[1] = res.second;
    calc(t);
    r = make_pair(t, res.second);
  }
  return r;
}

void tour(pt t, vector<int>* p) {
  if (n(t)) {
    return;
  }

  debug(t->ind);
  debug("L");
  tour(t->kids[0], p);  
  debug("R");  
  tour(t->kids[1], p);
  p->push_back(t->ind);
}
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  pt t;
  Treap foo(0);
  t = &foo;
  debug(t->ind);
  for (int i = 1; i < n; ++i) {
    debug(i);
    debug(t->ind);
    Treap tmp(i);
    debug(t->ind);  
    t = unite(t, &tmp);
  {
    vector<int> res;
    tour(t, &res);
    debug(res);  
  }
  }

  debug(t->ind);

  {
    vector<int> res;
    tour(t, &res);
    debug(res);  
  }


  auto sp = [&](pt x, pt y, int size) {
    auto res = split(x, size);
    x = res.first;
    y = res.second;
  };

  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    if (a >= b) {
      continue;
    }
    int sz = min(n - b, b - a);
    vector<pt> s(5);
    sp(s[0], t, a);
    sp(s[1], t, sz);
    sp(s[2], t, b - a - sz);
    sp(s[3], t, sz);
    sp(s[4], t, n - b - sz);
    t = unite(s[4], t);
    t = unite(s[1], t);
    t = unite(s[2], t);
    t = unite(s[3], t);
    t = unite(s[0], t);
  }
  vector<int> res;
  tour(t, &res);
  for (auto el : res) {
    cout << el + 1 << ' ';
  }
}