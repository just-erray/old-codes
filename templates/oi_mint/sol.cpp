// author: erray
#include <bits/stdc++.h>
 
using namespace std;

constexpr int md = int(1e9) + 7;

template<typename T> inverse(T x) {
  int p = md - 2;
  T res = 1;
  while (p > 0) {
    if (p & 1) {
      res *= x;
    }   
    x *= x;
    p >>= 1;
  }
  return res;
}

struct Mint {
  int value = 0;
  Mint normalize(Mint x) {
    return Mint(x.value);
  }
  template<typename T> int normalize(T x) {
    int res;
    if (x <= md || x >= md) {
      res = x % md;
    } else {
      res = x;
    }
    if (res < 0) {
      res += md;
    }
    return res;
  }
  template<typename T> Mint (T x) {
    *this = normalize(x);
  }
  Mint& operator+=(Mint ot) { 
    if (value += ot.value >= md) {
      value -= md;
    }
    return *this;
  }
  template<typename T> Mint& operator+=(T x) {
    return *this += Mint(x);
  }
  /*
  Mint& operator-=( Mint& ot) {
    if (value -= ot.value < 0) {
      value += md;
    }
    return *this;
  }
  template<typename T> Mint& operator-=(T x) {
    return *this -= Mint(x);
  }
  Mint& operator*=( Mint& ot) {
    value = normalize(1LL * value * ot.value);
    return *this;
  }
  template<typename T> Mint& operator*=(T x) {
    return *this *= Mint(x);
  }
  Mint& operator/=(Mint ot) {
    return *this *= inverse(ot);
  }
  template<typename T> Mint& operator/=(T x) {
    return *this *= Mint(x);
  }
  */
};

bool operator==(Mint x, Mint y) { 
  return x.value == y.value;
}

template<typename T> bool operator==(Mint x, T y) {
  return x == Mint(y);
}
template<typename T> bool operator==(T x, Mint y) {
  return y == Mint(x);
}

bool operator!=(Mint x, Mint y) {
  return !(x == y);
}

template<typename T> bool operator!=(Mint x, T y) {
  return !(x == y);
}

template<typename T> bool operator!=(T x, Mint y) {
  return !(x == y);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  Mint x = 12;
  cout << int(x) << '\n';
}