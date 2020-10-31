// author: erray
#include<bits/stdc++.h>
 
using namespace std;

constexpr int md = 998244353;

int pw(int w) {
  int res = 1, cur = 27;
  while (w) {
    if (w & 1) {
      res = 1LL * res * cur % md;
    }
    cur = 1LL * cur * cur % md;
    w >>= 1;
  }
  return res;
}
 
struct Hash {
  int val, rval;
  int size;
  Hash() {
    size = 0;
    val = 0;
    rval = 0;
  }

  Hash(int v) : val(v), rval(v) {
    size = 1;
  }
  bool palind() {
    return val == rval;
  }
};

Hash operator+(const Hash& left, const Hash& right) {
  Hash res;
  res.size = left.size + right.size;
  res.val = (left.val + 1LL * pw(left.size) * right.val % md) % md;
  res.rval = (right.rval + 1LL * pw(right.size) * left.rval % md) % md;
  return res;
}

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

struct Treap {
  int prio, size, val;
  Hash v;
  vector<Treap*> c;

  Treap(int _v) : v(_v), val(_v) {
    size = 1;
    prio = (int) rng();
    c = {NULL, NULL};
  }
};

typedef Treap* pt;

int size(pt t) {
  return (t ? t->size : 0);
}

void re(pt t) {
  Hash left = (t->c[0] ? t->c[0]->v : Hash());
  Hash right = (t->c[1] ? t->c[1]->v : Hash());
  t->size = size(t->c[0]) + size(t->c[1]) + 1;
  t->v = left + Hash(t->val) + right;
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
  int lsz = size(t->c[0]);
  if (lsz >= v) {
    auto res = split(t->c[0], v);
    t->c[0] = res.second;
    re(t);
    return make_pair(res.first, t);  
  } else {
    v -= lsz + 1;
    auto res = split(t->c[1], v);
    t->c[1] = res.first;
    re(t);
    return make_pair(t, res.second);
  }
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  string s;
  cin >> n >> q >> s;
  pt root = new Treap(s[0] - 'a' + 1);
  
  auto add = [&](char c, int p) {
    pt a = new Treap(c - 'a' + 1);
    pt tmp;
    tie(root, tmp) = split(root, p);
    root = unite(unite(root, a), tmp);
  }; 

  for (int i = 1; i < n; ++i) {
    add(s[i], i);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r;
      cin >> l >> r;
      --l, --r;
      pt tmp, foo;
      tie(tmp, root) = split(root, l);
      tie(foo, root) = split(root, r - l + 1);
      root = unite(tmp, root);
    } else if (t == 2) {
      char c;
      int p;
      cin >> c >> p;
      add(c, p - 1);
    } else {
      int l, r;
      cin >> l >> r;
      --l, --r;
      pt left, right;
      tie(left, root) = split(root, l);
      tie(root, right) = split(root, r - l + 1);
      cout << (root->v.palind() ? "yes" : "no") << '\n';
      root = unite(unite(left, root), right);
    }
  }
}