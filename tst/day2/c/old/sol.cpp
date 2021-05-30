#include <bits/stdc++.h>

using namespace std;

using int128 = __int128;

string to_string(int128 x) {
  string res;
  if (x == 0) {
    res += "0";
    return res;
  }

  bool neg = false;
  if (x < 0) {
    neg = true;
    x *= -1;
  }
  while (x > 0) {
    res += char('0' + x % 10);
    x /= 10;
  }
  if (neg) {
    res += '-';
  }
  reverse(res.begin(), res.end());
  return res;
}

ostream& operator<<(ostream& out, int128 x) {
  out << to_string(x);
  return out;
}

template<typename A, typename B> string to_string(pair<A, B> p);
string to_string(string s) {
  return '"' + s + '"';
}

string to_string(const char* c) {
  return to_string(string(c));
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < int(v.size()); ++i) {
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T& v) {
  string res = "{";
  for (auto& e : v) {
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(e);
  }
  res += "}";
  return res;
}
 
template<typename A, typename B> string to_string(pair<A, B> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ')';
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << "  " << to_string(H);
  debug_out(T...);
}

#ifdef DEBUG 
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) void(37)
#endif


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> costs(m);
  for (int i = 0; i < n; ++i) {
    int a, c;
    cin >> a >> c;
    --a;
    costs[a].push_back(c);
  }

  debug(costs);

  for (int i = 0; i < m; ++i) {
    sort(costs[i].begin(), costs[i].end());
    for (int j = int(costs[i].size()) - 1; j > 0; --j) {
      costs[i][j] -= costs[i][j - 1];
    }
  }


  vector<int> left(m), right(m);
  vector<int> pas(m);
  for (int i = 0; i < m; ++i) {
    cin >> left[i] >> right[i];
    pas[i] = right[i] - left[i];
  }
  debug(left, right, costs);


  multiset<int128> no;
   int128 first = 0;
   for (int i = 0; i < m; ++i) {
     if (!costs[i].empty()) {
       first += 1LL * left[i] * costs[i][0];
     }
   }  

  const int N = (*max_element(right.begin(), right.end())) + 1;
  vector<multiset<int128>> act(N);

  auto Can = [&](int128 x) {
    debug(x, "START /*--------------------------------------------------------------------------*/");
    multiset<int128> in;
    if (first > x) {
      return no;
    }
    x -= first;
    debug(first);
    in.insert(0);
    debug(in, x);
    for (int i = 0; i < N; ++i) {
      act[i].clear();
    }

    for (int i = 0; i < m; ++i) {
      debug(i);
      vector<int128> add;
      auto Add = [&add](int128 y) {
        if (y != 0) {
          add.push_back(y);
        }
      };
      int size = int(costs[i].size());
      if (size == 0) {
        continue;
      }

      int128 cur_sum = 0;
      int till = left[i];
      for (int j = left[i]; j <= right[i]; ++j) {
        if (cur_sum <= x) {
          act[j].insert(cur_sum);
          Add(cur_sum);
          till = i;
          if (int(add.size()) + int(in.size()) >= k) {
            return no;
          }  
        } else {
          break;
        }
        cur_sum += costs[i][0];
      }
      debug(act);

      for (int p = 1; p < size; ++p) {
        int new_till = 1;
        int from = 1;
        if (p == 1) {
          from = left[i];
        }
        if (act[from].empty() || (*act[from].begin()) + costs[i][p] > x) {
          break;
        }
        for (int j = 1; j <= till; ++j) {
          from = max(from, j);
          int128 add_cost = 1LL * j * costs[i][p];
          if (act[from].empty() || (*act[from].begin()) + add_cost > x) {
            act[j].clear();
            //break;
          }
          multiset<int128> nw;
          for (int q = from; q <= till; ++q) {
            if (act[q].empty() || (*act[q].begin()) + add_cost > x) {
              act[q].clear();
            }
            new_till = q;
            for (auto e : act[q]) {
              if (e + add_cost > x) {
                break;
              }
              nw.insert(e + add_cost);
              Add(e + add_cost);
              if (int(add.size()) + int(in.size()) >= k) {
                 return no;
               }  
            }
          }
          act[j] = nw;
        } 
        debug(p, act);
        swap(till, new_till);
      }

      debug(add);

      vector<int128> add_later;
      for (auto e : add) {
        for (auto ee : in) {
          if (ee + e > x) {
            break;
          }
          //debug(e, ee, e + ee);
          add_later.push_back(e + ee);
          if (int(add_later.size()) + int(in.size()) >= k) {
            debug(add_later);
            return no;
          }
        }
      }
      debug(add_later);
      for (auto e : add_later) {
        in.insert(e);
      }
      debug(in);
    }
    debug(in, "RETURN");
    return in;
  };

  
  const int MAX = int(1e9);
  const int128 inf = int128(n) * m * MAX;
  //Can(inf);
  int128 low = first, high = inf;
  while (low < high) {
    int128 mid = (low + high) / 2;
    if (Can(mid).empty()) {
      high = mid;
    } else {
      low = mid + 1;
    }
    debug(low, high);
  }
  //low - 1 icin say, low olanlari say sonra 
  multiset<int128> in;  
  if (Can(low).empty()) {
    in = Can(low  - 1);
    while ((int) in.size() < k) {
      in.insert(low - first);
    }  
  } else {
    in = Can(low); 
    while ((int) in.size() < k) {
      in.insert(inf);
    }  
  }
    debug(costs);
    debug(left);
    debug(right);
    debug(low);

  assert(int(in.size()) == k);
  for (auto e : in) {
    cout << (e == inf ? int128(-1) : e + first) << '\n';
  }
}