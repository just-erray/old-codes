// author: erray
#include<bits/stdc++.h>
 
using namespace std;
template<typename T> class SuffixArray {
  public:
  int lg, sz;
  vector<vector<int>> sorted;
  vector<vector<int>> order;
  vector<int> last_order, last_sorted, lcp;
  vector<T> m;
  SuffixArray(vector<T> v) {
    m = v;
    assert(!v.empty());
    sz = (int) v.size();
    lg = 33 - __builtin_clz(sz - 1);
    order.resize(lg, vector<int>(sz));
    sorted.resize(lg, vector<int>(sz));
    for (int i = 0; i < sz; ++i) order[0][i] = v[i];
    iota(sorted[0].begin(), sorted[0].end(), 0);
    sort(sorted[0].begin(), sorted[0].end(), [&](int x, int y) {
      return order[0][x] < order[0][y];
    });
    for (int now = 1; now < lg; ++now) {
      int mx = *max_element(order[now - 1].begin(), order[now - 1].end()) + 1;
      int add = (1 << (now - 1));
      if (now == 1 && (mx > sz * 4 || *min_element(order[now - 1].begin(), order[now - 1].end()) < 0)) {
        vector<tuple<T, T, int>> srt(sz);
        for (int i = 0; i < sz - 1; ++i) {
          srt[i] = make_tuple(order[0][i], order[0][i + 1], i);
        }
        srt[sz - 1] = make_tuple(order[0][sz - 1], -1, sz - 1);
        sort(srt.begin(), srt.end());
        for (int i = 0; i < sz; ++i) {
          int foo1, foo2, ii;
          tie(foo1, foo2, ii) = srt[i];
          sorted[now][i] = ii;
        }
      } else {
        vector<int> size(mx), cur(mx);
        for (auto el : order[now - 1]) ++size[el];
        for (int i = 1; i < mx; ++i) cur[i] = cur[i - 1] + size[i - 1];
        for (int i = sz - add; i < sz; ++i) sorted[now][cur[order[now - 1][i]]++] = i;
        for (auto el : sorted[now - 1]) {
          if (el - add < 0) continue;
          sorted[now][cur[order[now - 1][el - add]]++] = el - add;
        }
      }
      for (int i = 0; i < sz; ++i) {
        if (i == 0) {
          order[now][sorted[now][i]] = 0;
          continue;
        }
        int con = sorted[now][i], bef = sorted[now][i - 1];
        if (order[now - 1][con] == order[now - 1][bef] && (con + add < sz ? order[now - 1][con + add] : -1) == (bef + add < sz ? order[now - 1][bef + add] : -1)) {
          order[now][con] = order[now][bef];
        } else order[now][con] = order[now][bef] + 1;
      }
    }
    last_sorted = sorted.back();
    last_order.resize(sz);
    for (int i = 0; i < sz; ++i) {
      last_order[i] = (int) order.back()[i];
    }
  }
  SuffixArray(string v) {
    assert(!v.empty());
    sz = (int) v.size();
    m.resize(sz);
    for (int i = 0; i < sz; ++i) m[i] = v[i];
    lg = 33 - __builtin_clz(sz - 1);
    order.resize(lg, vector<int>(sz));
    sorted.resize(lg, vector<int>(sz));
    for (int i = 0; i < sz; ++i) order[0][i] = v[i];
    iota(sorted[0].begin(), sorted[0].end(), 0);
    sort(sorted[0].begin(), sorted[0].end(), [&](int x, int y) {
      return order[0][x] < order[0][y];
    });
    for (int now = 1; now < lg; ++now) {
      int mx = *max_element(order[now - 1].begin(), order[now - 1].end()) + 1;
      int add = (1 << (now - 1));
      vector<int> size(mx), cur(mx);
      for (auto el : order[now - 1]) ++size[el];
      for (int i = 1; i < mx; ++i) cur[i] = cur[i - 1] + size[i - 1];
      for (int i = sz - add; i < sz; ++i) sorted[now][cur[order[now - 1][i]]++] = i;
      for (auto el : sorted[now - 1]) {
        if (el - add < 0) continue;
        sorted[now][cur[order[now - 1][el - add]]++] = el - add;
      }
      for (int i = 0; i < sz; ++i) {
        if (i == 0) {
          order[now][sorted[now][i]] = 0;
          continue;
        }
        int con = sorted[now][i], bef = sorted[now][i - 1];
        if (order[now - 1][con] == order[now - 1][bef] && (con + add < sz ? order[now - 1][con + add] : -1) == (bef + add < sz ? order[now - 1][bef + add] : -1)) {
          order[now][con] = order[now][bef];
        } else order[now][con] = order[now][bef] + 1;
      }
    }
    last_sorted = sorted.back();
    last_order.resize(sz);
    for (int i = 0; i < sz; ++i) {
      last_order[i] = (int) order.back()[i];
    }

  }
  vector<int> get_array() {
    return last_sorted;
  }
  int ord(int ind, int level = -1) {
    assert(level < lg);
    if (level == -1) return order.back()[ind];
    return order[level][ind];
  }
  T get(int ind, int after) {
    if (last_sorted[ind] + after >= sz) return -1;
    return m[last_sorted[ind] + after];
  }
  int lower_bound(int l, int r, int i, T c) {
    if (l > r) return sz;
    int ns = l, ne = r;
    while (ne - ns > 1) {
      int mid = (ne + ns) >> 1;
      if (get(mid, i) >= c) ne = mid;
      else ns = mid;
    }
    if (get(ns, i) != c && get(ne, i) != c) return sz;
    if (get(ns, i) == c) return ns;
    return ne;
  }
  int upper_bound(int l, int r, int i, T c) {
     if (l > r) return -1;
    int ns = l, ne = r;
    while (ne - ns > 1) {
      int mid = (ne + ns) >> 1;
      if (get(mid, i) > c) ne = mid;
      else ns = mid;
    }
    if (get(ns, i) != c && get(ne, i) != c) return -1;
    if (get(ne, i) == c) return ne;
    return ns;
  }
  int count(string s) {
    int l = 0, r = sz - 1;
    for (int i = 0; i < (int) s.size(); ++i) {
      l = lower_bound(l, r, i, s[i]);
      r = upper_bound(l, r, i, s[i]);
    }
    return max(r - l + 1, 0);
  }
  void build_lcp() {
    lcp.resize(sz - 1);
    for (int i = 1; i < sz; ++i) {
      int res = 0;
      int l = last_sorted[i - 1], r = last_sorted[i];
      for (int j = lg - 1; j >= 0; --j) {
        if (order[j][l] == order[j][r]) {
          int len = 1 << j;
          res += len;
          l += len;
          r += len;
        }
      }
      lcp[i - 1] = res;
    }
  }
  vector<int> get_lcp() {
    assert(!lcp.empty());
    return lcp;
  }
  /*
  SparseTable<int> st;
  int find_lcp(int r1, int r2) {
    assert(!lcp.empty());
    if (st.table.empty()) {
      SparseTable<int> foo(lcp, [&](int x, int y) {
        return min(x, y);
      });
      st = foo;
    }
    if (r1 == r2) return sz - r1;
    r1 = last_order[r1], r2 = last_order[r2];
    if (r1 > r2) swap(r1, r2);
    return st.get(r1, r2 - 1);
  }
  */
};
/*
sorted indexes == get_array()
order of the index in 2 ^ k range, no k means all string == ord(ind, k)
occurrence number of s == count(s)
lower bound from the last l and r at index i int c == lower_bound(l, r, i, c)
upper bound from the last l and r at index i int c == upper_bound(l, r, i, c)
build lcp array == build_lcp()
lcp array == get_lcp()
(uncomment in need with SparseTable) lcp of 2 index == find_lcp(index1 index2)
--=hash is necessery for long long=--
*/
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    long long ans = n * (n + 1) / 2;
    SuffixArray<char> sa(s);
    sa.build_lcp();
    auto g = sa.get_lcp();
    for (auto e : g) {
      ans -= e;
    }

    cout << ans << '\n';
  }  
}