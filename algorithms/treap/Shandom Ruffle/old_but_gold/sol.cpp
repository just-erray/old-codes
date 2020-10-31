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

struct Treap {
  int prio, ind, sz;
  vector<Treap*> c;

  Treap(int _ind);
};

Treap::Treap(int _ind) {
  c = {NULL, NULL};
  prio = (int) rng();
  ind = _ind;
  sz = 1;
}

typedef Treap* pt;

int size(pt t) {
  if (!t) {
    return 0;
  }
  return t->sz;
}

void re(pt t) {
  if (!t) {
    return;
  }
  t->sz = 1 + size(t->c[0]) +  size(t->c[1]);
}

void split(pt x, pt left, pt right, int v) {
  if (!x) {
    left = right = x;
    return;
  }
  assert(v <= size(x));

  int lsz = size(x->c[0]);

  if (lsz >= v) {
    split(x->c[0], left, x->c[0], v);
    right = x;
  } else {
    v = v - lsz;
    split(x->c[1], x->c[1], right, v);
    left = x;
  }
}

void unite(pt res, pt l, pt r) {
  if (!l) {
    res = r;
  } else if (!r) {
    res = l;
  } else if (l->prio > r->prio) {
    res->c[1] = unite(l->c[1], r);
    res->c[0] = l->c[0];
  } else {
    res->c[0] = unite(l, r->c[0]);
    res->c[1] = r->c[1];
  }
  re(res);
}

void tour(pt t, vector<int>& res) {
  if (!t) {
    return;
  }
  tour(t->c[0], res);
  tour(t->c[1], res);
  res.push_back(t->ind);
}
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  pt root;
  
  auto print = [&] {
    vector<int> res;
    tour(root, res);
    for (auto el : res) {
      cout << el << ' ';
    }
  };
  vector<pt> st;
  
  for (int i = 0; i < n; ++i) {
    pt tmp = new Treap(i);
    root = unite(root, tmp);
  }  

  print();
  pt tmp;
  tie(root, tmp) = split(root, 2);
  root = unite(tmp, root);
  print();
}