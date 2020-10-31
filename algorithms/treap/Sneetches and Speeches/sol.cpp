// author: erray
#include<bits/stdc++.h>
 
using namespace std;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

struct Treap {
  int prio;
  vector<Treap*> c;
  
  int v;
  int one;
  int ans;    
  int size;
  vector<bool> side;
  vector<int> ct;
  vector<int> lazy;

  Treap(char _v) : v(_v - '0' + 1){
    one = v;
    ans = 1;
    size = 1;
    side = {v, v};
    ct = {1, 1};         
    //lazy empty 
  }

  Treap() {
    one = 0;
    ans = 0;  
    size = 0;
    side = {0, 0};
    ct = {0, 0};
    //lazy empty
  }
}; 

typedef Treap* pt;

pt emp = new Treap();

pt get(pt t) {
  return (t ? t : emp);
}

void pull(pt t) {
  auto l = get(t->c[0]);
  auto r = get(t->c[1]);
  t->one = l->one + r->one + t->v;
  t->size = l->size + r->size + 1;
  if (t->c[0]) {
    t->side[0] = l->side[0];
  } else {
    t->side[0] = t->v;  
  }

  if (t->c[1]) {
    t->side[1] = r->side[1];
  } else {
    t->side[1] = t->v;
  }

  t->ct[0] = l->ct[0];
  t->ct[1] = r->ct[1];
  if ((l->one == l->size && r->one == r->size &&  t->v == 1) || (l->one + r->one == 0 && t->v == 0)) {
    t->ct[0] = t->ct[1] = t->size;
  }
  int ans = 0;
  if (l->side[1] == r->side[0] && l->side[1] == t->v) {
    ans = l->
  }

  t->ans = ans;
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}