#include <bits/stdc++.h>
#undef DEBUG

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
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first >> a[i].second;
  }
  sort(a.begin(), a.end());
  for (int i = n - 1; i >= 0; --i) {
    a[i].first -= a[0].first;
  }

  debug(a);
  vector<long long> pref(n);
  vector<long long> pref_sum(n + 1);
  long long sum = 0;
  long long ans = 0;
  const long long inf = (long long) 1e15;
  for (int i = 0; i < n; ++i) {
    int size = a[i].first;
    sum += a[i].second;
    pref_sum[i + 1] = sum;
    if (pref[i] + sum - size >= 0) {
      int low = 0, high = i;
      while (low < high) {
        int mid = (low + high) >> 1;
        if (sum - size + pref[mid] >= 0) {
          high = mid;
        } else {
          low = mid + 1;
        }
      }
      long long res = min(sum - pref_sum[low], (i == n - 1 ? inf : a[i + 1].first - 1) - (low == 0 ? -inf : a[low - 1].first + 1));
      debug(res);
      
      ans = max(ans, res);
    }
    if (i < n - 1) {
       debug(sum, a[i + 1].first);
      pref[i + 1] = max(pref[i], -sum + (a[i + 1].first));
    }
    debug(ans);
  }
  debug(pref);
  cout << ans << '\n';
}