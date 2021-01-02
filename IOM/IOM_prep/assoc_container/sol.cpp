// author: erray
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds; 
gp_hash_table<long long, int> freq;

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  pbds t;
  t.insert(1);
  t.insert(5);

  int x = t.order_of_key(2);
  cout << *t.find_by_order(x) << '\n';
}