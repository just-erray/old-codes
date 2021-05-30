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

string to_string(char c) {
  return string("'") + c + "'";
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  string res = "{";
  for (int i = 0; i < int(v.size()); ++i) {
    int e = v[i];
    if (int(res.size()) > 1) {
      res += ", ";
    }
    res += to_string(e);
  }
  res += "}";
  return res;
}

template<typename T> string to_string(T v) {
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
#d  efine debug(...) void(37)
#endif


constexpr int mod = int(1e9) + 7;
struct Mint {
  int value;
  template<typename T> int normalize(T x) {
    int res;
    if (-mod <= x && x < mod) {
      res = int(x);
    } else {
      res = int(x % mod);
    }
    if (res < 0) {
      res += mod;
    }
    return res;
  }

  Mint() : value() { }
  template<typename T> Mint(T x) { value = normalize(x); }
  const int& operator()() const { return value; }
  template<typename T> operator T() { return value; }
  Mint inverse(Mint x) {
    Mint res = 1;
    int p = mod - 2;
    while (p > 0) {
      if (p & 1) {
        res *= x;
      }
      x *= x;
      p >>= 1;
    }
    return res;
  }

  Mint& operator+=(Mint x) {
    if ((value += x.value) >= mod) {
      value -= mod;
    }
    return *this;
  }
  Mint& operator-=(Mint x) {
    if ((value -= x.value) < 0) {
      value += mod;
    }
    return *this;
  }
  Mint& operator*=(Mint x) {
    value = normalize(1LL * value * x.value);
    return *this;
  }
  Mint& operator/=(Mint x) {
    return *this *= inverse(x);
  }

  template<typename T> Mint operator+=(T x) {
    return *this += Mint(x);
  }
  template<typename T> Mint operator-=(T x) {
    return *this -= Mint(x);
  }
  template<typename T> Mint operator*=(T x) {
    return *this *= Mint(x);
  }
  template<typename T> Mint operator/=(T x) {
    return *this /= Mint(x);
  }
  Mint operator-() {
    value = mod - value;
    return *this;
  }
};

bool operator==(Mint x, Mint y) {
  return x.value == y.value;
}
template<typename T> bool operator==(Mint x, T y) {
  return x == Mint(y);
}
template<typename T> bool operator==(T x, Mint y) {
  return Mint(x) == y;
}

bool operator!=(Mint x, Mint y) {
  return x.value != y.value;
}
template<typename T> bool operator!=(Mint x, T y) {
  return x != Mint(y);
}
template<typename T> bool operator!=(T x, Mint y) {
  return Mint(x) != y;
}

Mint operator+(Mint x, Mint y) {
  return x += y;
}
template<typename T> Mint operator+(Mint x, T y) {
  return x += Mint(y);
}
template<typename T> Mint operator+(T x, Mint y) {
  return Mint(x) += y;
}

Mint operator-(Mint x, Mint y) {
  return x -= y;
}
template<typename T> Mint operator-(Mint x, T y) {
  return x -= Mint(y);
}
template<typename T> Mint operator-(T x, Mint y) {
  return Mint(x) -= y;
}

Mint operator*(Mint x, Mint y) {
  return x *= y;
}
template<typename T> Mint operator*(Mint x, T y) {
  return x *= Mint(y);
}
template<typename T> Mint operator*(T x, Mint y) {
  return Mint(x) *= y;
}

Mint operator/(Mint x, Mint y) {
  return x /= y;
}
template<typename T> Mint operator/(Mint x, T y) {
  return x /= Mint(y);
}
template<typename T> Mint operator/(T x, Mint y) {
  return Mint(x) /= y;
}

ostream& operator<<(ostream& out, Mint x) {
  out << x.value;
  return out;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}