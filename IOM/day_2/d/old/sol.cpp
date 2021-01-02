#include<bits/stdc++.h>

using namespace std;

template<typename A, typename B> string to_string(pair<A, B> p);
template<typename A, typename B, typename C> string to_string(tuple<A, B, C>);
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D>);

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(const char* p) {
  return to_string(string(p));
}

string to_string(char c) {
  return string("'") + c + "'";
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if ((int) res.size() > 1) {
      res += ", ";
    }             
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& el : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(el);
  }
  res += "}";
  return res;
}

template<typename A, typename B> string to_string(pair<A, B> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename A, typename B, typename C> string to_string(tuple<A, B, C> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ')';
}
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ", " + to_string(get<3>(t)) + ')';
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << "  " << to_string(H);
  debug_out(T...);
}


#ifdef LOCAL
#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) void(37)
#endif


struct SegTree {
  struct node {
    int l, r;
    unsigned int sum = 0;
    unsigned int tag = 0;

    void modify(unsigned int x) {
      sum += (r - l + 1) * x;
      tag += (r - l + 1) * x;
    }
  };

  int n;
  vector<node> tree;
  
  void push(int v, int rv) {
    if (tree[v].tag != 0) {
      tree[rv].modify(tree[v].tag);
      tree[v + 1].modify(tree[v].tag);
    }
    tree[v].tag = 0;
  }

  void build(int v, int l, int r, const vector<int>& form) {
    if (l == r) {
      tree[v].l = tree[v].r = form[l];
      return;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    build(v + 1, l, mid, form);
    build(rv, mid + 1, r, form);
    tree[v].l = tree[v + 1].l;
    tree[v].r = tree[rv].r;
  }
   
  void modify(int v, int l, int r, const int& ll, const int& rr, const unsigned int& x) {
    if (tree[v].l >= ll && rr >= tree[v].r) {
      tree[v].modify(x);
      return;
    }   

    if (tree[v].l > rr || tree[v].r < ll) {
      return;
    }

    int mid = (l + r) >> 1;
    int rv = l + ((mid - l + 1) << 1);
    push(v, rv);

    modify(v + 1, l, mid, ll, rr, x);
    modify(rv, mid + 1, r, ll, rr, x);
    tree[v].sum = tree[rv].sum + tree[v + 1].sum;
  }

  unsigned int get(int v, int l, int r, const int& ll, const int& rr) {
    if (tree[v].l >= ll && rr >= tree[v].r) {
      return tree[v].sum;
    }   

    if (tree[v].l > rr || tree[v].r < ll) {
      return 0;
    }

    int mid = (l + r) >> 1;
    int rv = l + ((mid - l + 1) << 1);
    push(v, rv);
    return get(v + 1, l, mid, ll, rr) + get(rv, mid + 1, r, ll, rr);
  }

  SegTree(const vector<int>& h) {
    n = (int) h.size();
    tree.resize((n << 1) - 1);
    build(0, 0, n - 1, h);
  }

  SegTree() { }

  unsigned int get(int ll, int rr) {
    assert(ll >= 0 && rr < n && ll >= rr);
    return get(0, 0, n - 1, ll, rr);
  }

  void modify(int ll, int rr, unsigned int x) {
    assert(ll >= 0 && rr < n && ll >= rr);
    modify(0, 0, n - 1, ll, rr, x);    
  }

};

struct SegTree2D {
  struct node {
    int l, r;
    SegTree me;
    vector<pair<int, int>> tag;
    void modify(int ll, int rr, unsigned int x) {
      me.modify(ll, rr, x);
      tag.emplace_back(ll, rr);
    }

    unsigned int get(int ll, int rr) {
      return me.get(ll, rr);
    }
  };

  int n;
  vector<node> tree;

  void push(int v, int l, int r) {
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
        
    while (!tree[v].tag.empty()) {
      tree[v + 1].modify(tree[v].tag.back().first, tree[v].tag.back().second, 1);  
      tree[rv].modify(tree[v].tag.back().first, tree[v].tag.back().second, 1);      
      tree[v].tag.pop_back();
    }
  }

  void build(int v, int l, int r, const vector<int>& h, const vector<int>& row) {
    tree[v].me = SegTree(row);
    if (l == r) {
      tree[v].l = tree[v].r = h[r];
      return;
    }

    int mid = (l + r) >> 1;
    int rv = l + ((mid - l + 1) << 1);
    build(v + 1, l, mid, h, row);
    build(rv, mid + 1, r, h, row);

  }

  void modify(int v, int l, int r, int ll, int rr, const int& lll, const int& rrr, const unsigned int& x) {
    if (tree[v].l > rr || tree[v].r < ll) {
      return;
    }
    
    if (tree[v].l >= ll && rr >= tree[v].r) {
      tree[v].modify(lll, rrr, x * uint32_t(rr - ll + 1));  
    }
    ll = max(ll, tree[v].l);
    rr = min(rr, tree[v].r);

    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);

    tree[v].me.modify(lll, rrr, x * uint32_t(rr - ll + 1));
    modify(v + 1, l, mid, ll, rr, lll, rrr, x);
    modify(rv, mid + 1, r, ll, rr, lll, rrr, x); 
  }

  uint32_t get(int v, int l, int r, const int& ll, const int& rr, const int& lll, const int& rrr) {
    if (tree[v].l > rr || tree[v].r < ll) {
      return 0;
    }
    
    if (tree[v].l >= ll && rr >= tree[v].r) {
       return tree[v].get(lll, rrr);
    }

    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, l, r);
    return get(v + 1, l, mid, ll, rr, lll, rrr) + get(rv, mid + 1, r, ll, rr, lll, rrr);
  }
  
  SegTree2D(vector<int>& col, vector<int>& row) : n((int) col.size()) {
    tree.resize((n << 1) - 1);
    build(0, 0, n - 1, col, row);  
  }

  uint32_t get(const int& ll, const int& rr, const int& lll, const int& rrr) {
    return get(0, 0, n - 1, ll, rr, lll, rrr);
  }
  void modify(const int& ll, const int& rr, const int& lll, const int& rrr) {
     modify(0, 0, n - 1, ll, rr, lll, rrr, 1);
  }

};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> row, col;
  vector<array<int, 5>> a(q);
  for (int i = 0; i < q; ++i) {
    int t;
    cin >> t;
    if (t == 1) {
      for (int j = 0; j < 5; ++j) {
        cin >> a[i][j];
      }
    } else {
      a[i][4] = -1;
      for (int j = 0; j < 4; ++j) {
        cin >> a[i][j];
      }
    }
    for (int j = 0; j < 4; ++j) {
      --a[i][j];
      if (j % 2 == 0) {
        row.push_back(a[i][j]);
      } else {
        col.push_back(a[i][j]);
      }
    }
  }

  sort(row.begin(), row.end());
  sort(col.begin(), col.end());
  row.erase(unique(row.begin(), row.end()), row.end());
  col.erase(unique(col.begin(), col.end()), col.end());
  SegTree2D st(row, col);
  for (auto[r1, c1, r2, c2, t] : a) {
    if (t == -1) {
      cout << st.get(r1, r2, c1, c2) << '\n';
    } else {
      st.modify(r1, r2, c1, c2);
    }
  }
}