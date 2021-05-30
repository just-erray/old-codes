// author: erray
#include <bits/stdc++.h>
 
using namespace std;

constexpr int md = 998244353;

struct Mint {
  int value;
  template<typename T> int normalize(T x) {
    int res = 0;
    if (-md <= value && value < md) {
      res = int(x);
    } else {
      res = int(x % md);
    }
    if (res < 0) {
      res += md;
    }
    return res;
  }
  Mint() : value() { } 
  template<typename T>  Mint(T x) : value(normalize(x)) { }
  const int& operator()() const { return value; }   
  template <typename T> operator T() const { return static_cast<T>(value); }
  template<typename T> T inverse(T x) {
    int p = md - 2;
    T res;
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
    if ((value += x.value) >= md) {
      value -= md;
    }
    return *this;
  }
  Mint& operator-=(Mint x) {
    if ((value -= x.value) < 0) {
      value += md;
    }
    return *this;
  }
  Mint& operator*=(Mint x) {
    value = normalize(1LL * value * x.value);
    return *this;
  }
  Mint& operator/=(Mint x) {
    value = normalize(1LL * value * inverse(x).value);
    return *this;
  }
  template<typename T> Mint& operator+=(T x) {
    return *this += Mint(x);
  }
  template<typename T> Mint& operator-=(T x) {
    return *this -= Mint(x);
  }
  template<typename T> Mint& operator*=(T x) {
    return *this *= Mint(x);
  }
  template<typename T> Mint& operator/=(T x) {
    return *this /= Mint(x);
  }
  Mint operator-() {
    return Mint(-value);
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

string to_string(Mint x) {
  return to_string(x.value);
}

istream& operator>>(istream& s, Mint& x) {
  long long in;
  s >> in;
  x = in;
  return s;
}

ostream& operator<<(ostream& s, Mint x) {
  s << x();
  return s;
}

template<typename T> Mint power(Mint x, T y) {
  assert(y >= 0);
  Mint res = 1;
  while (y > 0) {
    if (y & 1) {
      res *= x;
    }
    x *= x;
    y >>= 1;
  }
  return res;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}