#include <bits/stdc++.h>
using namespace std;

#define lli long long
#define endl "\n"
#define all(aa) aa.begin(), aa.end()
const lli INF = LLONG_MAX;

int main(){
  int n, k;
  cin>>n>>k;
  vector<int> m(k);
  int ans=k-1;
  cout<<(char)(ans+'a');
  for(int i = 1; i < n; i++){
    int tmp=ans;
    cout<<(char)(m[ans]+'a');
    ans=m[ans];
    m[tmp]=(m[tmp]+1)%k;
  }
}