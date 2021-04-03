// author: erray
#include<bits/stdc++.h>
 
using namespace std;
template<typename A, typename B> string to_string(const pair<A, B>& p);
template<typename A, typename B, typename C> string to_string(const tuple<A, B, C>& t);
template<typename A, typename B, typename C, typename D> string to_string(const tuple<A, B, C, D>& t);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char& c) {
  return "'"s + c + "'";
}

string to_string(const char *c) {
  return to_string(string(c));
}

string to_string(const bool& b) {
  return (b ? "true" : "false");
}

string to_string(const vector<bool>& v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if (i > 0) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<size_t T> string to_string(const bitset<T>& bs) {
  return bs.to_string();
}

template<typename T> string to_string(queue<T> q) {
  string res = "{";
  size_t sz = q.size();
  while (sz--) {
    T cur = q.front();
    q.pop();
    q.push(cur);
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(cur);
  }
  res += "}";
  return res;
}

template<typename T, class C> string to_string(priority_queue<T, vector<T>, C> pq) {
  vector<T> tmp;
  string res = "{";
  while (!pq.empty()) {
    T cur = pq.top();
    pq.pop();
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(cur);
    tmp.push_back(cur);
  }
  for (auto el : tmp) {
    pq.push(el);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(const T& v) {
  string res = "{";
  for (auto &el : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(el);
  }
  res += "}";
  return res;
}

template<typename A, typename B> string to_string(const pair<A, B>& p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename A, typename B, typename C> string to_string(const tuple<A, B, C>& t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ')';
}
template<typename A, typename B, typename C, typename D> string to_string(const tuple<A, B, C, D>& t) {
  return '(' + to_string(get<0>(t)) + ", " + to_string(get<1>(t)) + ", " + to_string(get<2>(t)) + ", " + to_string(get<3>(t)) + ')';
}

void debug_out(int size, bool first, string name) {
  vector<string> tmp = {name};
  vector<int> tmp2 = {size, first};
  cerr << endl;
}

constexpr int buffer_size = 255;

template<typename Head, typename... Tail> void debug_out(int size, bool first, string name, Head H, Tail... T) {
  string tmp;
  int off = 0;
  while ((!name.empty() && name[0] != ',') || off != 0) {
    tmp += name[0];
    name.erase(name.begin());
    char c = tmp.back();
    if (c == '{' || c == '(') {
      ++off;
    } else if (c == '}' || c == ')'){
      --off;
    }
  }
  if (!name.empty()) {
    name.erase(name.begin());
  }
  if (tmp[0] == ' ') {
    tmp.erase(tmp.begin());
  }

  string buff = to_string(H);
  if ((int) buff.size() + size + (int) tmp.size() > buffer_size - 5 && !first) {
    cerr << '\n';
    size = 0;
  }
  cerr << '[' << tmp << ": " << buff << "] ";
  debug_out(((int) buff.size() + size + (int) tmp.size() + 5) % buffer_size, false, name, T...);
}

#ifdef DEBUG
#define debug(...) cerr << "-> ", debug_out(3, true, string(#__VA_ARGS__), __VA_ARGS__)
#define here cerr << "-> " << __LINE__ << endl
#else
#define debug(...) void(37)
#define here void(37)
#endif
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }

  vector<vector<int>> b(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> b[i][j];
    }
  }

  set<pair<int, int>> no;
  vector<int> obs(m);
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (b[i][j] < b[i - 1][j]) {
        no.emplace(i, j);
        ++obs[j];
      }
    }
  } 

  queue<int> que;
  for (int i = 0; i < m; ++i) {
    if (obs[i] == 0) {
      que.push(i);
    }
  }

  auto Add = [&](int ind) {
    while (true) {
      auto er = no.lower_bound(make_pair(ind, -1));
      if (er == no.end() || er->first != ind) {
        break;
      }
      --obs[er->second];
      if (obs[er->second] == 0) {
        que.push(er->second);
      }
      no.erase(er);
    }
  };

  vector<int> ans;
  vector<pair<int, int>> splits(1, make_pair(0, n - 1));
  while (!que.empty()) {
    int col = que.front();
    que.pop();
    ans.push_back(col);
    vector<pair<int, int>> new_splits;
    for (auto[l, r] : splits) {
      int lst = l;
      for (int row = l + 1; row <= r; ++row) {
        assert(b[row][col] >= b[row - 1][col]);
        if (b[row][col] != b[row - 1][col]) {
          new_splits.emplace_back(lst, row - 1);
          Add(row);
          lst = row;
        }  
      }   
      new_splits.emplace_back(lst, r);
    }  
    
    swap(new_splits, splits);
  }

  set<pair<vector<int>, int>> st;
  for (int i = 0; i < n; ++i) {
    st.emplace(a[i], i); 
  }


  bool ok = true;
  for (auto[l, r] : splits) {
    int ind = -1;
    for (int i = l; i <= r; ++i) {
      auto me = st.lower_bound(make_pair(b[i], -1));
      int cur = me->second;
      st.erase(me);
      ok &= (ind < cur);
      ind = cur; 
    }
  }

  if (!ok) {
    cout << -1 << '\n';
    return 0;
  }
  cout << (int) ans.size() << '\n';
  reverse(ans.begin(), ans.end());
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
  cout << '\n';
}