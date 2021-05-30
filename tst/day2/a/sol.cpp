#include <bits/stdc++.h>

using namespace std;

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
  int n;
  cin >> n;
  constexpr int MAX = 27;

  using Tas = array<array<int, 2>, 2>;
  vector<Tas> a(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        char c;
        cin >> c;
        a[i][j][k] = c - 'A' + 1;
      }
    }
  }

  debug(a);
  const int MASK = (1 << 4);
  long long ans = 0;
  using Count = array<array<array<array<int, 27>, 27>, 27>, 27>;
  Count ct = {};
  auto Get = [&](Tas x) {
    return ct[x[0][0]][x[0][1]][x[1][0]][x[1][1]];
  };

  for (int i = 0; i < n; ++i) {
    Tas me = a[i];
    for (int mask = 0; mask < MASK; ++mask) {
      Tas need = {};
      bool invalid = false;
      auto Add = [&](int x, int y, int nw) {
        if (need[x][y] != nw && need[x][y] != 0) {
          invalid = true;
          return;
        }
        need[x][y] = nw;
      };

      int many = 0;
      if (mask & 1) {
        //left for me right for them
        Add(0, 1, me[0][0]);
        Add(1, 1, me[1][0]);
        ++many;
      }
      if ((mask >> 1) & 1) {
        //right for me, left for them
        Add(0, 0, me[0][1]);
        Add(1, 0, me[1][1]);
        ++many;
      }
      if ((mask >> 2) & 1) {
        //bottom for me, top for them
        Add(0, 0, me[1][0]);
        Add(0, 1, me[1][1]);
        ++many;
      }
      if ((mask >> 3) & 1) {
        //top for me, bottom for them
        Add(1, 0, me[0][0]);
        Add(1, 1, me[0][1]);
        ++many;
      }

      if (!invalid && many > 0 && Get(need) > 0) {
        debug(me, need, many);
        ans += 1LL * (many % 2 ? 1 : -1) * Get(need);
      }

    }  

    for (int mask = 0; mask < MASK; ++mask) {
      Tas add;
      for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 2; ++k) {
          int now = j * 2 + k;
          if ((mask >> now) & 1) {
            add[j][k] = 0;  
          } else {
            add[j][k] = me[j][k];
          }
        }
      }
      //debug(me, add); 
      ct[add[0][0]][add[0][1]][add[1][0]][add[1][1]]++;
    }      
  }
  cout << ans << '\n';
}