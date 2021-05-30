#include <bits/stdc++.h>

using namespace std;


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
    return res;
  }
  Mint() : value() { }
  template<typename T> Mint(T x) : value(x) { } 
  const int& operator()() const { return value; }
  template<typename T> operator T() const { return static_cast<T>(value); }
  Mint inverse(Mint x) {
    int p = mod - 2;
    Mint res = 1;
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




int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

}