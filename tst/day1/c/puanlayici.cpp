#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include "leyla.h"

using namespace std;
namespace {

int son_i = -1, son_degis = -1;
char s[100005];


void wrong_answer(const char *MSG) {
  printf("%s\n", MSG);
  exit(0);
}

}  // namespace


void yerlerini_degistir(int bir, int iki){
  if(son_i == son_degis)
    wrong_answer("birden fazla yerlerini degistirme");
  son_degis = son_i;
  if(bir > son_i or iki > son_i or bir < 1 or iki < 1)
    wrong_answer("yanlis yerlerini degistirme");
  char temp = s[bir];
  s[bir] = s[iki];
  s[iki] = temp;
}


int main() {
  int N;
  
  if (scanf("%s", s + 1) != 1) {
    fprintf(stderr, "inputta hata var.\n");
    exit(1);
  }
  N = strlen(s + 1);

  basla(N);

  for(int i = 1; i <= N; i++){
    if(s[i] != 'K' and s[i] != 'S'){
      fprintf(stderr, "inputta hata var.\n");
      exit(1);
    }
    son_i = i;
    yeni_top(s[i]);
  }

  for(int i = 1; i <= N; i++) {
    if(s[i] != s[N - i + 1]) {
      wrong_answer("palindrom degil bruh");
      assert(false);
      return 1;
    }
  }

  printf("dogru\n");
  return 0;
}
