// author: erray
#include<bits/stdc++.h>
 
using namespace std;

struct SegTree {
  struct node {
    vector<int> t;
    void modify(int x) {
        
    }
  };
  int n;
  vector<node> tree;

  node cal(const node& x, const node& y) {
    node res;
    merge(x.t.begin(), x.t.end(), y.t.begin(), y.t.end(), back_inserter(res.t));
    return res;
  }

  void pull(int v, int rv) {
    tree[v] = cal(tree[v + 1], tree[rv]);
  }

  void push(int v, int rv) {
    
  }

  void modify(int v, int l, int r, int ll, int rr, bool f) {
    if (l >= ll && rr >= r) {
      tree[v].modify((f ? 1 : -1));
      return;
    }
    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    push(v, rv);

    if (mid >= ll) {
      modify(v + 1, l, mid, ll, rr, f);  
    }

    if (mid < rr) {
      modify(rv, mid + 1, r, ll, rr, f);
    }

    pull(v, rv);
  }

  int get(int v, int l, int r) {
    if (l == r) {
      return l;
    }

    int mid = (l + r) >> 1;
    int rv = v + ((mid - l + 1) << 1);
    
  }


  void modify(int ll, int rr, bool f = true) {
    modify(0, 0, n - 1, ll, rr, f);
  }

  int get() {
    return get(0, 0, n - 1);
  }

  SegTree(int _n) : n(_n) {
    tree.resize((n << 1) - 1);
  }

};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int n = (int) s.size();
  
  vector<int> one(n + 1), zero(n + 1);
  for (int i = 0; i < n; ++i) {
    one[i + 1] = one[i] + (s[i] == '1');
    zero[i + 1] = zero[i] + (s[i] == '0');
  }

  SegTree st(n + 1);
  st.modify(0, 0, false);

  auto part = [&](int x, bool for_ans = false) {
    vector<pair<int, int>> all;
    for (int i = 0; i < n; i += x) {
      int left = -1, right = -1;
      int go = min(n, i + x);
      {
        int low = i, high = go;
        while (low < high) {
          int mid = 1 + ((low + high) >> 1);
          if (one[mid] - one[i] == 0) {
            low = mid;
          } else {
            high = mid - 1;
          }
        }
        right = low;
      } 

      if (zero[go] - zero[right] != 0) {
        return -1;
      }

      {
        int low = i, high = right;
        while (low < high) {
          int mid = ((low + high) >> 1);
          if (one[right] - one[mid] == 0 && zero[right] - zero[mid] == 0) {
            high = mid;
          } else {
            low = mid + 1;
          }
        }  
        left = low;
      
      }
      
      if (right == n) {
        right = n + i;

      }
      all.emplace_back(left - i, right - i);
    }

    for (auto[l, r] : all) {
      st.modify(l, r);  
    }

    int res = -1;
    if (st.get_max() == (int) all.size()) {
      res = st.get();
      if (!for_ans) {
        res = x - res;
        if (n % x == 0) {
          res = res * (int) all.size();
        } else {
          res = res * ((int) all.size() - 1) + max(0, n % x - (x - res));
        }
      }
    }
      
    for (auto[l, r] : all) {
      st.modify(l, r, false);  
    }
    return res;
  };

  auto create = [&](int w) {
    string res = s;
    int most = part(w, true);
    for (int i = 0; i < n; ++i) {
      if (i % w < most) {
        assert(res[i] != '1');
        res[i] = '0';
      } else {
        assert(res[i] != '0');
        res[i] = '1';
      }
    }
    return res;
  };

  auto solve = [&](int x) {
    int ans = -1;
    int rem = -1;

    for (int i = 1; i <= x; ++i) {

      auto tmp = part(i);

      if (tmp > ans) {
        ans = tmp;
        rem = i;
      }
    }
    if (ans == -1) {
      return make_pair(-1, ""s);
    }
    
    return make_pair(ans, create(rem));
  };

  auto a1 = solve(n);

  if (a1.first == -1) {
    return cout << -1, 0;
  }
  cerr << a1.first << '\n';
  cout << a1.second << '\n';
}