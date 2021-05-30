// author: erray
#include <bits/stdc++.h>
 
using namespace std;

struct SegTree {
  struct node {
    long long sum = 0;
    void modify(long long x) {
      sum += x;
    }
  };  

  int n;
  vector<node> tree;
  SegTree(int_ n) : n(_n) {
    tree.resize(n << 1);
  } 

  node get(int l, int r) {
    ++r;
    l += n;
    r += n;
    while (l < r) {
      if (l & 1) {
        
      }
    }
  }
  
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
}