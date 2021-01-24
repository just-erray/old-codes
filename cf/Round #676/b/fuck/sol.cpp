// author: erray
#include<bits/stdc++.h>
 
using namespace std;

template<typename T, typename F> string to_string(pair<T, F> p);
template<typename T, typename F, typename Tr> string to_string(tuple<T, F, Tr> p);
template<typename T, typename F, typename Tr, typename Th> string to_string(tuple<T, F, Tr, Th> p);
string to_string(string s) {
  return '"' + s + '"';
}
string to_string(char c) {
  return (string) "'" + c + "'";
}
string to_string(const char* p) {
  return to_string((string) p);
}
string to_string(bool B) {
  return (B ? "true" : "false");
}
string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < (int) v.size(); ++i) {
    if ((int) res.size() > 1) res += ", ";
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
template<size_t T> string to_string(bitset<T> bs) {
  return bs.to_string();
}
template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& el : v) {
    if ((int) res.size() > 1) res += ", ";
    res += to_string(el);
  }
  res += "}";
  return res;
}
template<typename T, typename F> string to_string(pair<T, F> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}
template<typename T, typename F, typename Tr> string to_string(tuple<T, F, Tr> p) {
  return '(' + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ')';
}
template<typename T, typename F, typename Tr, typename Th> string to_string(tuple<T, F, Tr, Th> p) {
    return '(' + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ')';
}
void debug_out() {
  cerr << endl;
}
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:" , debug_out(__VA_ARGS__)
#else
#define debug(...) (void) 37
#endif

class dsu {
  public:
  vector<int> par, ct;
  dsu(int n) {
    par.resize(n);
    ct.resize(n, 1);
    iota(par.begin(), par.end(), 0);
  }
  inline int get(int v) {
    return par[v] = (v == par[v] ? v : get(par[v]));
  }
  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return false;
    ct[x] += ct[y];
    par[y] = x;
    return true;
  }
};
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> grid[i][j];
      }
    }
    const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

    auto solve = [&](char c) {
      dsu d(n * n);
      auto convert = [&](int x, int y) {
        return x * n + y;
      };
      auto reconvert = [&](int x) {
        return make_pair(x / n, x % n);
      };

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (grid[i][j] == c) {
            continue;
          }
          if (i < n - 1 && grid[i + 1][j] != c) {
            d.unite(convert(i, j), convert(i + 1, j));
          }
          if (j < n - 1 && grid[i][j + 1] != c) {
            d.unite(convert(i, j), convert(i, j + 1));
          }
        }
      }
      vector<int> sc(n * n, n * n + 1), sf = sc;
      vector<pair<int, int>> bc(n * n), bf(n * n);
      auto range = [&](int x) {
        return x >= 0 && x < n;
      };
      
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          for (int x = -3; x < 4; ++x) {
            for (int y = -3; y < 4; ++y) {
              if (x + y == 0) {
                continue;
              }
              if (range(i + x) && range(j + y)) {
                if (d.get(convert(i + x, j + y)) == d.get(0)) {
                  if (abs(x) + abs(y) < sc[d.get(convert(i, j))]) {
                    sc[d.get(convert(i, j))] = abs(x) + abs(y);
                    bc[d.get(convert(i, j))] = make_pair(convert(i, j), convert(i + x, j + y));   
                  }
                }  
                if (d.get(convert(i + x, j + y)) == d.get(n * n - 1)) {
                  if (abs(x) + abs(y) < sf[d.get(convert(i, j))]) {
                    sf[d.get(convert(i, j))] = abs(x) + abs(y);
                    bf[d.get(convert(i, j))] = make_pair(convert(i, j), convert(i + x, j + y));   
                  }
                }  
              }
            }
          }
        }  
      }      
      vector<pair<int, int>> res;
      for (int i = 0; i < n * n; ++i) {
        auto[ax, ay] = reconvert(i);
        if (grid[ax][ay] == c) {
          continue;
        }
        sc[i]--;
        sf[i]--;
        if (sc[i] + sf[i] < 3) {
          if (sc[i] == 1) {
            {
              auto l = reconvert(bc[i].first);
              auto r = reconvert(bc[i].second);
              debug(l, r);            
              res.emplace_back((l.first + r.first) / 2, (l.second + r.second) / 2);
            }
            {
              auto l = reconvert(bf[i].first);
              auto r = reconvert(bf[i].second);
              res.emplace_back((l.first + r.first) / 2, (l.second + r.second) / 2);
            }
          } else if (sf[i] == 2) {
            auto l = reconvert(bf[i].first);
            auto r = reconvert(bf[i].second);
            debug(l, r);
            while (l.first != r.first) {
              if (l.first > r.first) {
                --l.first;
                if (l.first != r.first) res.push_back(l);  
              } else {
                ++l.first;
                if (l.first != r.first) res.push_back(l);              
              }
            }
            while (l.second != r.second) {
              if (l.second > r.second) {
                --l.second;
                if (l.second != r.second) res.push_back(l);  
              } else {
                ++l.second;
                if (l.second != r.second) res.push_back(l);              
              }
            }          
          }
        }
      }
      debug(res);
      return res;
    };
    
    auto ans = solve('0');
    if (ans.empty()) {
      ans = solve('1');
    }
    assert((int) ans.size() < 3);
    cout << (int) ans.size() << '\n';
    for (auto[x, y] : ans) {
      cout << x + 1 << ' ' << y + 1 << '\n';
    }
  }
}