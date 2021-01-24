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
  int n = (int) s.size();
  vector<int> sz(n);
  vector<string> ans(n);
  string cur;
  char bef = 0;
  int ct = 0;
  vector<char> del(256);
  for (int i = n - 1; i >= 0; --i) {
    if (i == n - 1 || s[i] != s[i + 1]) {
      ct = 1;
      bef = (cur.empty() ? 0 : cur.back());  
    }   
    if (bef == s[i] && del[s[i]] < s[i]) {
      debug(i); 
      bef = del[s[i]];
      cur.pop_back();
      --ct;
    } else if (bef == s[i]) {
      bef = del[s[i]];
      cur += s[i];
    } else if (ct % 2 || s[i] < bef) {
      cur += s[i];
    } else {
      cur.pop_back(); 
    }    
    sz[i] = (int) cur.size();
    if ((int) cur.size() > 10) {
      for (int j = 0; j < 5; ++j) {
        ans[i] += cur[(int) cur.size() - j - 1];
      }
      ans[i] += "..."s + cur[1] + cur[0];
    } else {
      reverse(cur.begin(), cur.end());
      ans[i] = cur;
      reverse(cur.begin(), cur.end());
    }
    ++ct;
    del[s[i]] = bef;
    assert(bef != s[i]);
  }
  for (int i = 0; i < n; ++i) {
    cout << sz[i] << ' ' << ans[i] << '\n';
  }
}