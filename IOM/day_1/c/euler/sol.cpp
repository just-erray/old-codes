#include<bits/stdc++.h>

using namespace std;

template<typename A, typename B> string to_string(pair<A, B>);
template<typename A, typename B, typename C> string to_string(tuple<A, B, C>);
template<typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D>);

string to_string(string s) {
  return '"' + s + '"';
}

string to_string(char c) {
  return "'"s + c + "'";
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
  for (const auto& el : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }  
    res += to_string(el);
  }
  res += "}";
  return res;
}


template<typename A, typename B> string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";  
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

const int N = (int) 2e5 + 5;
vector<int> g[N];
int deg[N];
vector<int> tour;

void dfs(int v, int pr) {
  tour.push_back(v);
  for (auto u : g[v]) {
    if (u == pr) {
      continue;
    }
    dfs(u, v);
  }     
} 

int get(int v, int& left, int pr) {
  if (left == 0) {
    return v + 1;
  } 
  --left;
  int res = -1;
  for (auto u : g[v]) {
    if (u == pr) {
      continue;
    }
    if (res != -1) {
      break;
    } 
    res = get(u, left, v);
  }
  return res; 
}



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    g[x].push_back(y);
    g[y].push_back(x);
    ++deg[x];
    ++deg[y];
  }
  for (int i = 0; i < n; ++i) {
    sort(g[i].begin(), g[i].end());
  }
  int ct = 0;
  for (int i = 0; i < n; ++i) {
    ct += (deg[i] == 1);
  }

  if (ct == n - 1) { 
    debug("hello there"s);
    int mid = 0;
    while (deg[mid] == 1) {
      ++mid;
    }  
    while (q--) {
      long long k;
      cin >> k;
      --k;
      int s = k / n;
      int left = k % n;
      cout << s + 1 << ' ';
      if (s == mid) {
        cout << (left ? g[mid][left - 1] : mid) + 1 << '\n';
      } else {
        if (left == 0) {
          cout << s + 1 << '\n';
        } else if (left == 1) {
          cout << mid + 1 << '\n';
        } else {
          int now = g[mid][left - 2];
          if (now >= s) {
            now = g[mid][left - 1];
          }
          cout << now + 1 << '\n';
        }
      }
    }


    return 0;
  }

  if (ct == 2) {
    int start = 0;
    while (deg[start] != 1) {
      ++start;
    }
    vector<int> o;
    int bef = -1;
    while (bef == -1 || deg[start] != 1) {
      o.push_back(start);
      for (auto u : g[start]) {
        if (u != bef) {
          bef = start;
          start = u;
          break;
        }
      }  
    }
    o.push_back(start);
    vector<int> no(n);
    for (int i = 0; i < n; ++i) {
      no[o[i]] = i;
    }
    while (q--) {
      long long k;
      cin >> k;
      --k;
      int s = k / n;
      int left = k % n;
      cout << s << ' ';
      if (deg[s] == 1) {
        cout << (no[s] == 0 ? o[left] : o[n - left - 1]) + 1 << '\n';
      } else {
        if (o[no[s] - 1] < o[no[s] + 1]) {
          cout << (no[s] >= left ? o[no[s] - left] : o[no[s] + (left - no[s])]) + 1 << '\n';
        } else {
          cout << (n - no[s] - 1 >= left ? o[no[s] + left] : o[no[s] - (left - (n - no[s] - 1))]) + 1 << '\n'; 
        }
      }
    }

    return 0;     
  }

  dfs(0, -1);
  while (q--) {
     long long x;
     cin >> x;
     --x;
     if (x < n) {
       cout << 1 << ' ' << tour[x] + 1 << '\n';
     } else {
       int left = x % n;
       cout << x / n + 1 << ' ' << get(x / n, left, -1) << '\n';
     }
  }  
}