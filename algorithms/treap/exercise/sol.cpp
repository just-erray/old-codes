// author: erray
#include<bits/stdc++.h>
 
using namespace std;
mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

struct Treap {
  array<Treap*, 2> c;
  int ind;
  long long sum;
  long long tag;
  int l, r;
  int prio;
  Treap(int _ind, int x) : c({0, 0}), sum(x), ind(_ind), tag(0), prio(int(rng())), l(ind), r(ind) { }

  void modify(long long x) {
    sum += x;
    tag += x;
  }
  
  void push() {
    for (int j = 0; j < 2; ++j) {
      if (c[j] != 0) {
        c[j]->modify(tag);
      }
    } 
    tag = 0;
  }

  void pull() {
    sum = 0;
    if (c[0]) {
      sum += c[0]->sum;
      l = c[0]->l;
    }
    
    if (c[1]) {
      sum += c[1]->sum;
      r = c[1]->r;
    }
  }
};

typedef Treap* pt;

pt unite(pt x, pt y) {
  if (x == 0) {
    return y;  
  }

  if (y == 0) {
    return x;
  }
  
  if (x-> ind > y->ind) {
    swap(x, y);
  }

  if (x -> prio > y->prio) {
    x->push();
    x->c[1] = unite(c->c[1], y);  
  } else {
    y->push();
    y->c[0] = unite(c, y->c[0]);
  }
}

  
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
}