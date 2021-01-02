// author: erray
#include<bits/stdc++.h>
 
using namespace std;
 
int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  struct node {
    node* left, *right;
    int val = -1;
  };

  typedef node* pt;
  pt root = new node;

  function<void(pt)> dfs = [&](pt v) {
    int x;
    cin >> x;
    if (x == 0) {
      v->left = new node;
      v->right = new_node;
      dfs(v->left);
      dfs(v->right);
    } else {
      v->val = x - 1;
    }
  };
  dfs(root);
  

}