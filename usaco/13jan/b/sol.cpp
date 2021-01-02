// author: erray
#include<bits/stdc++.h>
 
using namespace std;

const int N = (int) 1e2;

struct e {
  int r = 0, s = 0;
};

e dp[N][N];
string a[N];
e mv[N][N];
bool done[N][N];

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  #ifndef LOCAL
  string P = "skicourse";
  freopen((P + ".in").c_str(), "r", stdin);
  freopen((P + ".out").c_str(), "w", stdout);
  #endif 
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    for (int j = 0; j < m; ++j) {
      if (a[i][j] == 'S') {
        mv[i][j].s = true;
      } else {
        mv[i][j].r = true;
      }
    }
  }

  int best = min(n, m);
  int ans = best;
  int gone = 0;
  int mm = n * m;

  while (ans > 1 && gone < mm) {
    memcpy(dp, mv, sizeof(mv));

    int res = 0;
    int si = -1, sj = -1;

    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
        dp[i][j].s = dp[i][j].s * (min({dp[i][j - 1].s, dp[i - 1][j].s, dp[i - 1][j - 1].s}) + 1);
        dp[i][j].r = dp[i][j].r * (min({dp[i][j - 1].r, dp[i - 1][j].r, dp[i - 1][j - 1].r}) + 1);
        int mx = max(dp[i][j].s, dp[i][j].r);
        if (!done[i][j] && mx > res) {
          res = mx;
          si = i, sj = j;
        }
      }
    }

    ans = min(ans, res);
    done[si][sj] = true;

    for (int i = 0; i > -res; --i) {
      for (int j = 0; j > -res; --j) {
        int ni = si + i, nj = sj + j;
        gone += !(mv[ni][nj].r && mv[ni][nj].s);
        mv[ni][nj].r = mv[ni][nj].s = true;
      }
    }

  }

  cout << ans << '\n';      
}