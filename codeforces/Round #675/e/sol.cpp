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
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  const int n = (int) s.size();
  char bef = 0, best = 0;
  int ct = 1;  
  string ans;       
  vector<string> res(n);
  vector<int> size(n);
  for (int i = n - 1; i >= 0; --i) {
    debug(i, s[i], best, bef);
    char c = s[i];
    if (bef == s[i]) {
      if (s[i] >= best) {
        if (ct % 2) {
          ans += s[i];
        } else {
          assert(!ans.empty());
          ans.pop_back();
        }
      } else {
        ans += s[i];
      }

    } else {
      if (ans.empty()) {
        best = 0;
      } else {
        best = ans.back();
      }
      ans += s[i];
      ct = 1;
    }


    ++ct;
    bef = s[i];
    size[i] = (int) ans.size();
    if ((int) ans.size() <= 10) {
      reverse(ans.begin(), ans.end());
      res[i] = ans;
      reverse(ans.begin(), ans.end());        
    } else {
      for (int j = 0; j < 5; ++j) {
        res[i] += ans[(int) ans.size() - j - 1];
      }
      res[i] += "...";
      res[i] += ans[1];
      res[i] += ans[0];
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << size[i] << ' ' << res[i] << '\n';
  }                  
}