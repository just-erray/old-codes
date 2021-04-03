// author: erray
#undef __GLIBCXX_DEBUG
#include<bits/stdc++.h>
 
using namespace std;

using CHT_type = int;

struct line {
  mutable CHT_type x, y, sect;
  // x katsayi, y sabit, sect degisken icin buyuk olan ilk sayi
  bool operator<(CHT_type ot) const {
    return sect < ot;
    //query icin en iyi denklemi bulma
  }
  bool operator<(const line& ot) const {
    return x < ot.x;
    //denklemler kendi icinde katsayilarina gore siralaniyor
  }
};


struct CHT : set<line, less<>> {
  const CHT_type MAX = numeric_limits<CHT_type>::max();
  void intersect(iterator cur, iterator next) {
    if (next == end()) {
      //sonrasi yoksa sect olabilecek en buyuk sayidir
      cur->sect = MAX;
      return;  
    }   

    //sabitin buyuklugu devam ettirdigi ilk degiskeni hesaplama
    cur->sect = (cur->y - next->y) / (next->x - cur->x);
  } 

  bool add(CHT_type x, CHT_type y) {
    auto cur = insert(line{x, y, 0}).first;
    //denklemi ekle ve iteratorunu cur'e esitleme
    auto big = next(cur);
    //sonraki iteratorunu big'e esitle
    if (big != end() && big->y >= cur->y) {
      //eger denklem hull'in altinda kaliyosa silme
      erase(cur);
      return false;
    }

    while (cur != begin() && prev(cur)->y <= cur->y) {
      //yeni denklem eklendikten sonra hull'in disinda kalan denklemleri silme 
      cur = erase(prev(cur));
    }

    //cur icin en buyuk cevabi sagladigi son degiskeni bulma
    intersect(cur, next(cur));
    if (cur != begin()) {
      //cur'den onceki denklem icin en buyuk cevabi sagladigi son degiskeni bulma 
      intersect(prev(cur), cur);
    }
    return true;
  }

  int64_t get(CHT_type x) {
    //denklemlerin sect(en buyuk cevabi sagladiklari son deger)'e gore binary search atarak denklemi bulma
    auto me = lower_bound(x);
    //bu denkleme x degiskenini vererek sonucu dondurme
    return me->y + (int64_t) me->x * x;
  }
};

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  CHT c;
  c.add(0, 0);
  for (int i = 0; i < n; ++i) {
    char q;
    cin >> q;
    if (q == 'G') {
      int x;
      cin >> x;
      cout << c.get(x) << '\n';  
    } else {
      int x, y;
      cin >> x >> y;
      c.add(x, y); 
    }
  } 

  cerr << clock() << '\n';
}