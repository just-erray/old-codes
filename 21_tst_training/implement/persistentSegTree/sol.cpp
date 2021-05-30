// author: erray
#include <bits/stdc++.h>
 
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
 
struct node {
  int mx = 0;
  int tag = 0;
  void modify(int x) {
    mx += x;
    tag +=x;
  }
};

node emp;

node unite(const node& x, const node& y) {
  node res;
  res.mx = max(x.mx, y.mx);
  return res;
}

struct Node {
  node me;
  void modify(int x) {
    me.modify(x);
  }
  Node* l = 0;
  Node* r = 0;
  Node() { }
  Node(Node* x) {
    me = x->me;
    l = x->l;
    r = x->r;
  }
};

void pull(Node* v) {
  v->me = unite(v->l->me, v->r->me);
}

void push(Node* v) {
  if (v->me.tag != emp.tag) {
    v->l = new Node(v->l);
    v->r = new Node(v->r);
    v->l->modify(v->me.tag);  
    v->r->modify(v->me.tag);
    v->me.tag = emp.tag;
  }
}

void build(Node* v, int l, int r) {
  debug(l, r);
  if (l == r) {
    return;
  }  
  v->l = new Node();
  v->r = new Node();
  int mid = (l + r) >> 1;
  build(v->l, l, mid);
  build(v->r, mid + 1, r);
} 


Node* modify(Node* v, int l, int r, int ll, int rr, int x) {
  debug(l, r, ll, rr, x);
  push(v);
  Node* new_v = new Node(v);
  if (l >= ll && rr >= r) {
    new_v->modify(x);
    return new_v; 
  }
  int mid = (l + r) >> 1;
  if (mid >= ll) {
    new_v->l = modify(v->l, l, mid, ll, rr, x);
  }
  if (mid < rr) {
    new_v->r = modify(v->r, mid + 1, r, ll, rr, x);
  }
  pull(new_v);
  return new_v; 
}

node get(Node* v, int l, int r, int ll, int rr) {
  //debug(l, r, ll, rr);
  if (l >= ll && rr >= r) {
    return v->me;
  }
  int mid = (l + r) >> 1;
  push(v);
  if (mid >= ll && mid < rr) {
    return unite(get(v->l, l, mid, ll, rr), get(v->r, mid + 1, r, ll, rr));
  } else if (mid >= ll) {
    return get(v->l, l, mid, ll, rr);
  } else {
    return get(v->r, mid + 1, r, ll, rr);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Node*> roots(n + 1);
  roots[0] = new Node();
  build(roots[0], 0, n - 1);
  for (int i = 0; i < n; ++i) {
    roots[i + 1] = modify(roots[i], 0, n - 1, i, i, i + 1); 
  }

  //debug("modified");

  for (int ver = 1; ver <= n; ++ver) {
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
         cout << ver << ' ' << i << ' ' << j << ' ' << get(roots[ver], 0, n - 1, i, j).mx << '\n';   
      }
    }
  }
}