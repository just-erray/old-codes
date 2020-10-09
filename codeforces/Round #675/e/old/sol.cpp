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
  s += '$';
  char best = s.back()  ;
  vector<bool> erase;
  for (int i = n - 1; i >= 0; --i) {
    debug(best, i);
    int ct = 1;
    while (i > 0 && s[i] == s[i - 1]) {
      ++ct;
      --i;      
    }  
    if (ct % 2) {
      if (best <= s[i]) {
        erase.push_back(true);
        best = s[i];                
      } else {
        erase.push_back(false);
        best = s[i];                      
      }   
    } else {
      if (best <= s[i]) {
        erase.push_back(true);
      } else {
        erase.push_back(false);
        best = s[i];      
      }    
    }
    for (int j = 1; j < ct; ++j) {
      erase.push_back(erase.back());
    }
  }
  reverse(erase.begin(), erase.end());
  assert((int) erase.size() == n);
  
  vector<int> ct;
  string ans;
  vector<int> inds;
  for (int i = 0; i < n; ++i) {
    debug(i, s[i], (int) erase[i]);
    int cnt = 1;
    while (i < n - 1 && s[i] == s[i + 1]) {
      ++i;
      ++cnt;
    } 
    if (erase[i]) {
      if (cnt % 2) {
        ans += s[i];
        inds.push_back(i);
      }
    } else {
      ans += string(cnt, s[i]);
      for (int j = 0; j < cnt; ++j) {
        inds.push_back(i - cnt + j + 1);
      }
    }
    ct.push_back(cnt);
    for (int j = 1; j < cnt; ++j) {
      ct.push_back(ct.back());
    }
  }
  assert(ans.size() == inds.size());
  debug(ans);
  debug(inds);
  debug(erase);

  int go = 0;  
  int sz = (int) ans.size();
  auto write = [&] {
    debug("casual");
    cout << sz - go << ' ';
    if (sz - go > 10) {
      for (int j = go, sy = 0; sy < 5; ++sy, ++j) {
        cout << ans[j];
      }
      cout << "...";
      cout << ans[sz - 2] << ans[sz - 1];       
    } else {
      for (int j = go; j < sz; ++j) {
        cout << ans[j];
      }
    }
    cout << '\n';
  };

  auto writeC = [&](char c) {
    debug("extra");
    cout << sz - go + 1 << ' ';
    cout << c;
    if (sz - go + 1 > 10) {
      for (int j = 0, sy = 0; sy < 4; ++sy, ++j) {
        cout << ans[j];
      }
      cout << "...";
      cout << ans[sz - 2] << ans[sz - 1];       
    } else {
      for (int j = go; j < sz; ++j) {
        cout << ans[j];
      }
    }
    cout << '\n';
  };

  debug(ct);
  char lst = '$';
  int count = 1;  
  int p = 0;
  
  write();
  for (int i = 0; i < n - 1; ++i) {  
    if (lst != s[i]) {
      count = 1;          
    }
    if (p < (int) inds.size() && inds[p] == i) {
      ++p;
      ++go;
    }
    debug(count);
    if (erase[i]) {
      if (count % 2 == 1) {
        if (ct[i] % 2 == 1) {
          debug(ct[i], count);
          if (ct[i] == count) {
            write();
          } else {
            ++go;
            write();
            --go;  
          }
        } else {
          writeC(s[i]);      
        }
      } else {
        write();
      }
    } else {
      write();
    } 
    debug("second");
    lst = s[i];
    ++count;
  }
}