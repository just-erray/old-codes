//author: erray
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
  for (int i = 0; i < (int) v.size(); ++i) {
    if (i) {
      res += ", ";
    }
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T v) {
  string res = "{";
  for (auto& e : v) {
    if ((int) res.size() > 1) {
      res += ", ";
    }
    res += to_string(e);
  }
  res += "}";
  return res;
}

template<typename A, typename B> string to_string(pair<A, B> p) {
  return '(' + to_string(p.first) + ", " + to_string(p.second) + ")";
}

void debug_out() {
  cerr << endl;
}

template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
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
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
    --a[i].first, --a[i].second;
  } 
  if (n == 1) {
    cout << a[0].second - a[0].first + 1 << '\n';
    return 0;
  }

  sort(a.begin(), a.end());
  multiset<int> inc;
  for (auto[x, y] : a) {
    inc.insert(y);
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int l = a.back().first;
    if (i == n - 1) {
      l = a[n - 2].first;    
    }
    inc.erase(inc.find(a[i].second));
    int r = *inc.begin();
    inc.insert(a[i].second);
    ans = max(ans, max(0, r - l + 1) + a[i].second - a[i].first + 1);
  }

  auto big = a.back();
  a.pop_back();
  sort(a.begin(), a.end(), [&](auto x, auto y) {
    return make_pair(x.second, x.first) < make_pair(y.second, y.first);
  });

  debug(a, big);

  vector<int> suf(n);
  suf.back() = big.second - big.first + 1;
  for (int i = n - 2; i >= 0; --i) {
    suf[i] = max(0, min(a[i].second, big.second) - big.first + 1);
  }
  debug(suf);

  ans = max(ans, suf.front());
  int highest = 0;
  for (int i = 0; i < n - 1; ++i) {
    highest = max(highest, a[i].first);
    debug(highest);
    ans = max(ans, suf[i + 1] + max(0, a[0].second - highest + 1));
  }

  cout << ans << '\n';
}

