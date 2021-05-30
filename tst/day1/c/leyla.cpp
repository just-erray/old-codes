#include <bits/stdc++.h>
#include "leyla.h"

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

template<typename T> string to_string(const T& v) {
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


vector<int> a;
int n;
int mid;
void basla(int _n){
  n = _n;
  mid = n / 2;
  a.resize(n);
}

int size = 0;
array<int, 2> ct;
bool diff = false;

void Swap(int x, int y) {
  assert(x < size && y < size);
  swap(a[x], a[y]);
  yerlerini_degistir(x + 1, y + 1);  
}

void yeni_top(char renk) {
  int added = 0;
  if (renk == 'K') {
    a[size] = 0;
    added = 0;  
    ++ct[0];
  } else {
    a[size] = 1;
    added = 1;
    ++ct[1];
  }
  ++size;
  if (size <= n / 2 + 1) {
    return;
  }

  if (size == n) {
    ct[added] -= 1;
    if (ct[0] % 2 == 1) {
      if (a[0] != a[n - 1]) {
        Swap(0, mid);
      }
    } else {
      if (a[0] != a[n - 1]) {
        Swap(mid, n - 1);
      }
    }
  } else {
    int pal = n - size;
    //ciftse ayni tekse farkli mid'le 0
    if (a[size - 1] != a[pal]) {
      if (a[mid] != a[size - 1]) {
        Swap(mid, size - 1);
      } else {
        Swap(mid, pal);
      }
    }
  }
  debug(a);

}