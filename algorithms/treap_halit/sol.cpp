// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

struct node {
  int size = 1;
  char me;
  int prio;
  node* left;
  node* right;
  node() { }
  node(char _c) : me(_c) {
    prio = rng();
    left = right = NULL;
  }
};

typedef node* Treap;

int sz(Treap x) {
  return (x ? x->size : 0);
}

void calc(Treap x) {
  x->size = 1 + sz(x->left) + sz(x->right);
}

Treap unite(Treap x, Treap y) {
  if (x == 0) {
    return y;
  }
  if (y == 0) {
    return x;
  }

  if (x->prio > y->prio) {
    x->right = unite(x->right, y);
    calc(x);
    return x;
  } else {
    y->left = unite(x, y->left);
    calc(y);
    return y;
  }
}

pair<Treap, Treap> split(Treap x, int size) {
  if (x == 0) {
    return make_pair(x, x);
  }


  
  int left_size = sz(x->left);  
  debug(x->me, left_size);
  if (left_size >= size) {
    auto res = split(x->left, size);
    x->left = res.second;
    calc(x);
    return make_pair(res.first, x);
  } else {
    size -= left_size;
    auto res = split(x->right, size); 
    x->right = res.first;
    calc(x);
    return make_pair(x, res.second);
  }
}

void path(Treap x) {
  if (x == 0) {
    return;
  }
  path(x->left);
  cout << x->me;
  path(x->right);
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  Treap root = new node(s[0]);
  for (int i = 1; i < n; ++i) {
    Treap add = new node(s[i]);
    root = unite(root, add);
  }

  while (m--) {
    int l, r;
    cin >> l >> r;
    Treap mid, right;
    tie(root, mid) = split(root, l - 1);
    tie(mid, right) = split(mid, r - l + 1);
    #ifdef DEBUG 
    path(root);
    cout << '\n';
    path(mid);
    cout << '\n';
    path(right);
    cout << '\n';
    #endif
    
    root = unite(root, right);
    root = unite(root, mid);
    #ifdef DEBUG 
    path(root);
    cout << '\n';
    #endif
  }

  path(root);
}