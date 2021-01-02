// author: erray
#include<bits/stdc++.h>
 
using namespace std;

struct PersSegTree {
  struct node {
    node* l = 0, *r = 0;
    long long sum = 0;

    node(node* x) : l(x->l), r(x->r) {
      sum = 0;  
    }

    node() { }

    void modify(int w) {
      sum += w;
    }
  };
  vector<node*> me;
  int n;

  void pull(node* x) {
    x->sum = x->r->sum + x->l->sum;
  }

  node* modify(node* v, int l, int r, int t, int w) {
    node* add = new node(v);
    add->l = v->l;
    add->r = v->r;
    if (l == 0 && r == n - 1) {
      me.push_back(add);
    }
    
    if (l == r) {
      add->modify(w);
      return add;
    }

    int mid = (l + r) >> 1;
    if (mid >= t) {
      add->l = modify(add->l, l, mid, t, w);
    } else {
      add->r = modify(add->r, mid + 1, r, t, w); 
    }
    pull(add);
    return add;
  }
  
  long long get(node* v, int l, int r, int ll, int rr) {
    if (l >= ll && rr >= r) {
      return v->sum;
    }
    int mid = (l + r) >> 1;
    if (mid >= ll) {
      if (mid < rr) {
        return get(v->l, l, mid, ll, rr) + get(v->r, mid + 1, r, ll, rr);
      } else {
        return get(v->l, l, mid, ll, rr);
      }          
    } else {
      return get(v->r, mid + 1, r, ll, rr);
    }
  }

  void build(node* v, int l, int r) {
    int mid = (l + r) >> 1;
    if (mid != l) {
      v->l = new node;
      build(v->l, l, mid);
    }
    
    if (mid < r - 1) {
      v->r = new node;
      build(v->r, mid + 1, r);
    }
  }

  PersSegTree(int _n) : n(_n) {
    node* root = new node;
    me.push_back(root);
    build(root, 0, n - 1);
  }

  void modify(int over, int t, int w) {
    assert(t >= 0 && t < n && over <= (int) me.size() && over > 0);  
    modify(me[over - 1], 0, n - 1, t, w);
  }

  long long get(int over, int ll, int rr) {
    assert(ll >= 0 && ll < n && ll <= rr && over <= (int) me.size() && over > 0);
    return get(me[over - 1], 0, n - 1, ll, rr);
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  PersSegTree st(n);
  while (q--) {
    int t, l, r, v;
    cin >> t >> l >> r >> v;
    if (t == 1) {
      st.modify(v, l, r);
    } else {
      cout << st.get(v, l, r) << endl;
    }
  }
}