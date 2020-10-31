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

// modular template by tourist
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}

template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }

  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }

  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
    int64_t q = static_cast<int64_t>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

  template <typename U>
  friend const Modular<U>& abs(const Modular<U>& v) { return v; }

  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend std::istream& operator>>(std::istream& stream, Modular<U>& number);

 private:
  Type value;
};

template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
  return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {
  return stream << number();
}

template <typename T>
std::istream& operator>>(std::istream& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, int64_t>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

/*
using ModType = int;
struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/

constexpr int md = (int) 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

const int base = 27;

Mint Hash(int sz, Mint cur, Mint add) {
  return cur + power(Mint(base), sz) * add;
}

struct Treap {
  int prio, sz, own;
  Mint v;
  vector<Treap*> c;

  Treap(int _own) : v(_own), own(_own) {
    prio = (int) rng();
    sz = 1;
    c = {NULL, NULL};
  }
};

typedef Treap* pt;

void tour(pt t, string& res) {
  if (!t) {
    return;
  }
  tour(t->c[0], res);
  res.push_back(char('a' - 1 + t->own));
  tour(t->c[1], res);
}

#ifdef DEBUG
void path(pt t) {
  string foo;
  tour(t, foo);
  cerr << foo << endl;
}
#else
void path(pt t) {
  return;
}
#endif

int size(pt t) {
  if (!t) {
    return 0;
  }
  return t->sz;
}

Mint hash_w(pt t) {
  if (!t) {
    return 0;
  }
  return t->v;
}

void re(pt t) {
  if (!t) {
    return;
  }
  t->sz = 1 + size(t->c[0]) + size(t->c[1]);
  t->v = Hash(size(t->c[0]), hash_w(t->c[0]), Mint(t->own));
  t->v = Hash(size(t->c[0]) + 1, t->v, hash_w(t->c[1]));
}

pt unite(pt l, pt r) {
  if (!l) {
    return r;
  }
  if (!r) {
    return l;
  }
  
  if (l -> prio > r->prio) {
    l->c[1] = unite(l->c[1], r);
    re(l);
    return l;  
  } else {
    r->c[0] = unite(l, r->c[0]);
    re(r);
    return r;
  }
} 

pair<pt, pt> split(pt t, int v) {
  if (!t) {
    return make_pair(t, t);
  }
  if (size(t->c[0]) >= v) {
    auto l = split(t->c[0], v);
    t->c[0] = l.second;
    re(t);
    return make_pair(l.first, t);
  } else {
    auto r = split(t->c[1], v - size(t->c[0]) - 1);
    t->c[1] = r.first;
    re(t);
    return make_pair(t, r.second);
  }
}

bool p(pt t, Mint lhash, Mint rhash, int left, int right, const int& sz, int get) {      
  debug(lhash, rhash, left, right, sz, get);
  cerr << "subtree = "; path(t);
  if (!t) {
    assert(false);
  }  
  int lsz = size(t->c[0]); 
  debug(lsz);
  if (lsz == get) {
    rhash = Hash(size(t->c[1]), hash_w(t->c[1]), rhash);
    lhash = Hash(left, lhash, Hash(size(t->c[0]), hash_w(t->c[0]), Mint(sz & 1 ? 0 : t->own)));
    debug(lhash, rhash);
    return rhash == lhash;
  } else if (lsz > get) {
    debug("left");
    rhash = Hash(size(t->c[1]) + 1, Hash(1, t->own, Mint(hash_w(t->c[1]))), rhash); 
    return p(t->c[0], lhash, rhash, left, right, sz, get);
  } else {
    get -= lsz + 1;
    debug("right");
    lhash = Hash(left, lhash, Hash(size(t->c[0]), hash_w(t->c[0]), Mint(t->own)));
    left += size(t->c[0]) + 1;
    return p(t->c[1], lhash, rhash, left, right, sz, get);
  }

} 
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  pt root = new Treap(s[0] - 'a' + 1);
  for (int i = 1; i < n; ++i) {
    pt tmp = new Treap(s[i] - 'a' + 1);
    root = unite(root, tmp);
  }
  path(root);

  while (q--) {
    int t, l, r;
    cin >> t;
    if (t == 1) {
      cin >> l >> r;
      --l, --r; 
      vector<pt> com(2);
      tie(com[0], root) = split(root, l);
      tie(com[1], root) = split(root, r - l + 1);
      root = unite(com[0], root);
    } else if (t == 2) {
      char c;
      int p;
      cin >> c >> p;
      c -= 'a' - 1;
      pt tmp;
      tie(tmp, root) = split(root, p);
      pt add = new Treap(c);
      path(add);
      path(tmp);
      tmp = unite(tmp, add);
      root = unite(tmp, root);
    } else {
      cin >> l >> r;
      --l, --r;     
      vector<pt> com(2);
      tie(com[0], root) = split(root, l);
      tie(root, com[1]) = split(root, r - l + 1);
      debug(r, l);
      cout << (p(root, 0, 0, 0, 0, r - l + 1, (r - l) / 2) ? "yes" : "no") << '\n';
      root = unite(root, com[1]);
      root = unite(com[0], root);
    }
    path(root);
  }
}