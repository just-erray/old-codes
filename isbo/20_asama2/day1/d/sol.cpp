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

#define int long long
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  if (n % 2 == 1) {
    vector<int> odd(n + 1);
    vector<int> even(n + 1);
    for (int i = 0; i < n; ++i) {
      odd[i + 1] = odd[i];
      even[i + 1] = even[i];
      if (i % 2) {
        odd[i + 1] += a[i];
      } else {
        even[i + 1] += a[i];
      }
    } 
    int ans = max(even[n], odd[n]);
    for (int i = 0; i < n; ++i) {
      if (i % 2 == 0) {
        continue;
      }
      int prev = odd[i + 1] + even[n] - even[i + 1];
      int next = even[i] + odd[n] - odd[i];
      ans = max(ans, min(prev, next));
    }

    int smallest = LLONG_MAX;
    int dec = (long long) 1e17;
    int last = (long long) 1e17;
    for (int i = 0; i < n; ++i) {
      if (i % 2 == 1) {
        continue;
      }  
      smallest = min(smallest, odd[n] - odd[i + 1] + even[i + 1] + dec);
      dec = min(dec, last);
      last = -even[i + 1] + odd[i + 1];
    }

    ans = max(ans, smallest);
    cout << ans << ' ' << accumulate(a.begin(), a.end(), 0LL) - ans << '\n';
  } else {
    assert(false);
  }
}                     